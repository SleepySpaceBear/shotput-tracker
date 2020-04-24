#include "ui.hpp"

#include "app.hpp"

UI::UI(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size) {
	
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
}

void UI::OnLoadVideo(wxCommandEvent& event) {

}

void UI::OnAbout(wxCommandEvent & event) {
	wxMessageBox("This is a project for CS321",
		"About Shotput Tracker", wxOK | wxICON_INFORMATION);
}

void UI::OnExit(wxCommandEvent & event) {
	Close(true);
}

wxBEGIN_EVENT_TABLE(UI, wxFrame)
EVT_MENU(EV_LOAD_VIDEO, UI::OnLoadVideo)
EVT_MENU(wxID_ABOUT, UI::OnAbout)
EVT_MENU(wxID_EXIT, UI::OnExit)
wxEND_EVENT_TABLE();