#ifndef APP_HPP
#define APP_HPP

#include "ui.hpp"
#include "video.hpp"

#include "wx/app.h"

/*
 * A class representing the entirety of the application.
 * This class keeps track of things at the application level,
 * and it is called upon the UI for functionality.
 */
class App : public wxApp {
public:

	virtual bool OnInit() override;
	virtual int OnExit() override;

	// callback function for idling
	void OnIdle(wxIdleEvent& evt);

	// loads the video at the given path
	// returns true if successful and false otherwise
	bool LoadVideo(std::string& path);

	// public getter for the loaded video
	Video& GetVideo();
private:
	// the UI
	UI* m_ui;
	// the currently loaded video
	Video m_video;

	wxDECLARE_EVENT_TABLE();
};

wxDECLARE_APP(App);

#endif