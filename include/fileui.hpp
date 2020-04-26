#ifndef FILEUI_HPP
#define FILEUI_HPP

#include "wx/wx.h"
#include "wx/filectrl.h"

/*
 * A class representing the file selection UI for this program.
 * It calls upon the App class as needed through the wxGetApp function
 */
class FileUI : public wxFrame {
public:
	// public constructor
	FileUI(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	wxFileCtrl* m_fileSelector;

	// callback function for selecting a file
	void OnFileSelection(wxFileCtrlEvent& event);
	// callback function for closing the window
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif
