#include "ui.hpp"

#include "app.hpp"

UI::UI(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxMenu *menuFile = new wxMenu;
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
}

void UI::OnExit(wxCommandEvent & event) {
	Close(true);
}

void UI::OnAbout(wxCommandEvent & event) {
	wxMessageBox("This is a project for CS321",
		"About Shotput Tracker", wxOK | wxICON_INFORMATION);
}

wxBEGIN_EVENT_TABLE(UI, wxFrame)
EVT_MENU(wxID_EXIT, UI::OnExit)
EVT_MENU(wxID_ABOUT, UI::OnAbout)
wxEND_EVENT_TABLE();