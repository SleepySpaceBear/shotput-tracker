#include "app.hpp"

#include "ui.hpp"

bool App::OnInit() {
	m_ui = new UI("Shotput Tracker", wxPoint(50, 50), wxSize(450, 340));
	m_ui->Show(true);

	m_alive.store(true);
	m_threadWorker = std::thread([this] { this->work(); });

	return true;
}

int App::OnExit() {
	m_alive.store(false);
	m_threadWorker.join();
	return 0;
}

void App::OnIdle(wxIdleEvent& event) {
	event.RequestMore();
}

bool App::LoadVideo(std::string& path) {
    bool temp = m_vidCapture.open(path);
	m_video.setWidth(m_vidCapture.get(cv::CAP_PROP_FRAME_WIDTH));
	m_video.setHeight(m_vidCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
	m_video.setFramerate(m_vidCapture.get(cv::CAP_PROP_FPS));
	return temp;
}

VideoBuffer& App::GetVideoBuffer() {
	return m_video;
}

void App::work() {
	while (m_alive.load()) {
		if (m_vidCapture.isOpened()) {
			cv::Mat frame;
			if (m_vidCapture.read(frame)) {
				m_tracker.processFrame(frame);
				m_video.addFrame(matToBitmap(frame));
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
}

wxBitmap App::matToBitmap(const cv::Mat& mat) {

	int numPixels = m_video.getWidth() * m_video.getHeight();

	// allocate data for the image
	unsigned char* data = (unsigned char*) malloc(numPixels * 3);

	int numBytes = numPixels * 3;

	// convert from BGR to RGB
	for (int i = 0; i < numBytes; i += 3) {
		data[i] = mat.data[i + 2];
		data[i + 1] = mat.data[i + 1];
		data[i + 2] = mat.data[i];
	}

	wxImage image(m_video.getWidth(), m_video.getHeight(), data, true);
	wxBitmap temp(image);
	free(data);
	return temp;
}

wxBEGIN_EVENT_TABLE(App, wxApp)
EVT_IDLE(App::OnIdle)
wxEND_EVENT_TABLE();

wxIMPLEMENT_APP(App);
