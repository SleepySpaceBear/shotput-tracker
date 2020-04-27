#include "ui.hpp"

#include "app.hpp"
#include "fileui.hpp"

UI::UI(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER)) {
	
	wxMenu *menuFile = new wxMenu;
	wxMenuItem* loadVideo = new wxMenuItem(menuFile, EV_LOAD_VIDEO, "Load Video", "Select a video to load");
	menuFile->Append(loadVideo);
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);

	m_pVideoView = new VideoView(this, &wxGetApp().GetVideo());
	wxGetApp().SetTopWindow(this);
}

void UI::OnLoadVideo(wxCommandEvent& event) {
	FileUI* fileUI = new FileUI("Select a video file", wxPoint(50, 50), wxSize(480, 360));
	fileUI->Show(true);
}

void UI::OnAbout(wxCommandEvent & event) {
	wxMessageBox("This is a project for CS321",
		"About Shotput Tracker", wxOK | wxICON_INFORMATION);
}

void UI::OnExit(wxCommandEvent & event) {
	Close(true);
}

void UI::OnIdle(wxIdleEvent& event) {
	Video& video = wxGetApp().GetVideo();
	if (video.isLoaded()) {
		SetClientSize(video.getWidth(), video.getHeight());
	}
}

wxBEGIN_EVENT_TABLE(UI, wxFrame)
EVT_MENU(EV_LOAD_VIDEO, UI::OnLoadVideo)
EVT_MENU(wxID_ABOUT, UI::OnAbout)
EVT_MENU(wxID_EXIT, UI::OnExit)
EVT_IDLE(UI::OnIdle)
wxEND_EVENT_TABLE();