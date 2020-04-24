#include "fileui.hpp"

#include "app.hpp"

FileUI::FileUI(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxCLOSE_BOX)) {
	
	// so we can start the file search in <USERDIR>/Videos
	std::string defaultDir = getenv("USERPROFILE");
	defaultDir += "\\Videos";

	m_fileSelector = new wxFileCtrl(this, 1, defaultDir);
}

void FileUI::OnFileSelection(wxFileCtrlEvent& event) {
	std::string path = m_fileSelector->GetFilename().ToStdString();
	
	Close();
	
	wxGetApp().LoadVideo(path);
}

wxBEGIN_EVENT_TABLE(FileUI, wxFrame)
EVT_FILECTRL_FILEACTIVATED(1, OnFileSelection)
wxEND_EVENT_TABLE();
