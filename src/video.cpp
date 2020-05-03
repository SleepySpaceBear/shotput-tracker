#include "video.hpp"

#include <chrono>

Video::Video() {
	m_threadFrameConverter = std::move(std::thread([this] { this->work(); }));
}

Video::~Video() {
	m_alive.store(false);
	m_threadFrameConverter.join();
}

bool Video::open(std::string& path) {		
	{
		std::unique_lock<std::mutex> lk{ m_curFrame.mutStateChange };

		// clear previous video info
		m_vecBitmaps.clear();
		m_vidCapture.release();

		m_vidCapture.open(path, cv::CAP_FFMPEG);

		if (!m_vidCapture.isOpened()) {
			return false;
		}

		m_nWidth = m_vidCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		m_nHeight = m_vidCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		m_dFramerate = m_vidCapture.get(cv::CAP_PROP_FPS);

		if (m_curFrame.state != Video::FrameState::CONVERTED && m_curFrame.state != Video::FrameState::NOFRAME) {
			m_curFrame.cvStateChange.wait(lk, [this] { return this->m_curFrame.state == FrameState::CONVERTED; });
		}

		m_curFrame.state = Video::FrameState::NOFRAME;
	}
	m_curFrame.cvStateChange.notify_all();
	
	return true;
}

int Video::getNumFrames() const {
	return m_vecBitmaps.size();
}

wxBitmap Video::getDisplayFrame(int frameNum) const {
	// wait if we don't have a frame to show
	if (m_vecBitmaps.empty()) {
		std::unique_lock<std::mutex> lk{ m_curFrame.mutStateChange };
		m_curFrame.cvStateChange.wait(lk, [this] { return !this->m_vecBitmaps.empty(); });
	}

	// clamp frameNum at the max value
	if (m_vecBitmaps.size() <= frameNum) {
		frameNum = m_vecBitmaps.size() - 1;
	}

	return m_vecBitmaps.at(frameNum);
}

Video::Frame& Video::getFrame() {
	return m_curFrame;
}

bool Video::isLoaded() const {
	return m_vidCapture.isOpened();
}

int Video::getWidth() const {
	return m_nWidth;
}

int Video::getHeight() const {
	return m_nHeight;
}

double Video::getFramerate() const {
	return m_dFramerate;
}

void Video::work() {
	using namespace std::chrono_literals; // for using ms

	while (m_alive) {
		loadFrame();
		convertFrame();

		// now let's give this thread some rest if it can have it
		std::unique_lock<std::mutex> lk(m_curFrame.mutStateChange);
		m_curFrame.cvStateChange.notify_all();
		m_curFrame.cvStateChange.wait_for(lk, 10ms); 
	}

	return;
}

void Video::loadFrame() {
	if (m_curFrame.state == FrameState::CONVERTED || m_curFrame.state == FrameState::NOFRAME) {
		std::unique_lock<std::mutex> lk(m_curFrame.mutStateChange);
		// double check condition
		if (m_curFrame.state == FrameState::CONVERTED || m_curFrame.state == FrameState::NOFRAME) {

			m_vidCapture.read(m_curFrame.mat);

			if (m_curFrame.mat.empty()) {
				m_curFrame.state = FrameState::NOFRAME;
			}
			else {
				m_curFrame.state = FrameState::UNPROCESSED;
			}
		}

	}
	m_curFrame.cvStateChange.notify_all();
}

void Video::convertFrame() {
	if (m_curFrame.state == FrameState::PROCESSED) {
		std::unique_lock<std::mutex> lk(m_curFrame.mutStateChange);
		// double check the right condition
		if (m_curFrame.state == FrameState::PROCESSED) {

			int numPixels = m_nWidth * m_nHeight;

			// allocate data for the image
			unsigned char* data = (unsigned char*) malloc(numPixels * 3);

			// convert from BGR to RGB
			for (int i = 0; i < numPixels; i++) {
				data[3 * i] = m_curFrame.mat.data[3 * i + 2];
				data[3 * i + 1] = m_curFrame.mat.data[3 * i + 1];
				data[3 * i + 2] = m_curFrame.mat.data[3 * i];
			}

			wxImage image(m_nWidth, m_nHeight, data, true);
			m_vecBitmaps.emplace_back(image);
			m_curFrame.state = FrameState::CONVERTED;
		}
	}
	m_curFrame.cvStateChange.notify_all();
}