#include "app.hpp"

#include "ui.hpp"

bool App::OnInit() {
	m_ui = new UI("Shotput Tracker", wxPoint(50, 50), wxSize(450, 340));
	m_ui->Show(true);
	return true;
}

int App::OnExit() {
	return 0;
}

void App::OnIdle(wxIdleEvent& event) {
	event.RequestMore();
}

bool App::LoadVideo(std::string& path) {
	// open the video file for reading
	m_video.open(path);

    // if not successful, exit program
    if (!m_video.isLoaded())
    {
        return false;
    }

    return true;
}

Video& App::GetVideo() {
	return m_video;
}

wxBEGIN_EVENT_TABLE(App, wxApp)
EVT_IDLE(App::OnIdle)
wxEND_EVENT_TABLE();

wxIMPLEMENT_APP(App);
