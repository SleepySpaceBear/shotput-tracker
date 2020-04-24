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

void App::LoadVideo(std::string& path) {

}

wxIMPLEMENT_APP(App);