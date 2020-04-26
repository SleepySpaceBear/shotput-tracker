#include "app.hpp"

#include "ui.hpp"

bool App::OnInit() {
	UI *frame = new UI("Shotput Tracker", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

int App::OnExit() {
	return 0;
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

wxIMPLEMENT_APP(App);
