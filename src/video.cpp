#include "video.hpp"

bool Video::open(std::string& path) {	
	// clear frames 
	m_frames.clear();

	cv::VideoCapture cap(path, cv::CAP_FFMPEG);
	
	if (!cap.isOpened()) {
		return false;
	}

	m_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	m_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	m_framerate = cap.get(cv::CAP_PROP_FPS);

	cv::Mat mat;

	while (cap.read(mat)) {
		m_frames.emplace_back(mat.clone());
	}

	return !m_frames.empty();
}

int Video::getNumFrames() const {
	return m_frames.size();
}

wxBitmap Video::getDisplayFrame(int frameNum) const {
	int numPixels = m_width * m_height;
	
	// allocate data for the image
	unsigned char* data = (unsigned char*) malloc(numPixels * 3);
	
	for (int i = 0; i < numPixels; i++) {
		data[3 * i] = m_frames.at(frameNum).data[3 * i + 2];
		data[3 * i + 1] = m_frames.at(frameNum).data[3 * i + 1];
		data[3 * i + 2] = m_frames.at(frameNum).data[3 * i];
	}

	wxImage image(m_width, m_height, data, true);
	wxBitmap bitmap(image);
	
	free(data);
	
	return bitmap;
}

cv::Mat Video::getProcFrame(int frameNum) const {
	return cv::Mat(m_frames.at(frameNum));
}

bool Video::isLoaded() const {
	return m_width != -1 && m_height != -1 && !m_frames.empty();
}

int Video::getWidth() const {
	return m_width;
}

int Video::getHeight() const {
	return m_height;
}

double Video::getFramerate() const {
	return m_framerate;
}
