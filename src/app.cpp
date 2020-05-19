#include "app.hpp"

#include "constants.hpp"
#include "ui.hpp"
#include <analyzer_0.h>

// thread for the companion Analyzer
// for now, it starts in App::OnInit(){}
std::thread thread0;

bool App::OnInit() {

	// opens up the companion Analyzer
	//thread0 = std::thread(&Analyzer::foo, new Analyzer(), 5);


	m_ui = new UI("Shotput Tracker", wxPoint(50, 50), wxSize(450, 340));
	m_ui->Show(true);


	m_alive.store(true);
	m_threadWorker = std::thread([this] { this->work(); });;


	return true;
}


int App::OnExit() {
	m_alive.store(false);
	m_threadWorker.join();
	thread0.join();
	return 0;
}

void App::OnIdle(wxIdleEvent& event) {
	event.RequestMore();

}

bool App::LoadVideo(std::string& path) {
	std::unique_lock<std::mutex> lk{ m_mutVidCapture };
    
	bool temp = m_vidCapture.open(path);
	m_video.clear();
	
	if (temp) {
		m_video.setWidth(m_vidCapture.get(cv::CAP_PROP_FRAME_WIDTH) / SPT_VID_SCALE_FACTOR);
		m_video.setHeight(m_vidCapture.get(cv::CAP_PROP_FRAME_HEIGHT) / SPT_VID_SCALE_FACTOR);
		m_video.setFramerate(m_vidCapture.get(cv::CAP_PROP_FPS));
	}
	
	return temp;
}

VideoBuffer& App::GetVideoBuffer() {
	return m_video;
}

void App::work() {
	while (m_alive.load()) {
		std::unique_lock<std::mutex> lk{ m_mutVidCapture };
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
	const int numBytes = mat.rows * mat.cols * 3;

	// allocate data for the image
	unsigned char* data = (unsigned char*) malloc(numBytes);

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
