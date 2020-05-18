#ifndef APP_HPP
#define APP_HPP

#include <atomic>
#include <thread>

#include "ui.hpp"
#include "tracker.hpp"
#include "video.hpp"

#include "wx/app.h"

/*
 * A class representing the entirety of the application.
 * This class keeps track of things at the application level,
 * and it is called upon the UI for functionality.
 */
class App : public wxApp {
public:
	App() = default;
	~App() = default;

	virtual bool OnInit() override;
	virtual int OnExit() override;

	// callback function for idling
	void OnIdle(wxIdleEvent& evt);

	// loads the video at the given path
	// returns true if successful and false otherwise
	bool LoadVideo(std::string& path);

	// public getter for the video buffer
	VideoBuffer& GetVideoBuffer();
private:
	// the UI
	UI* m_ui;
	
	// the processed video
	VideoBuffer m_video;

	// the video capture
	cv::VideoCapture m_vidCapture;
	std::mutex m_mutVidCapture;
	
	// the tracker
	Tracker m_tracker;

	// worker thread
	std::thread m_threadWorker;

	// signal for m_threadWorker to remain alive
	std::atomic<bool> m_alive;
	
	// function for m_threadWorker
	void work();

	// converts cv::Mat to wxBitmap
	wxBitmap matToBitmap(const cv::Mat& mat);



	wxDECLARE_EVENT_TABLE();
};

wxDECLARE_APP(App);

#endif