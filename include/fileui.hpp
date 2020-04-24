#ifndef FILEUI_HPP
#define FILEUI_HPP

#include "wx/wx.h"
#include "wx/filectrl.h"

class FileUI : public wxFrame {
public:
	FileUI(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	wxFileCtrl* m_fileSelector;

	void OnFileSelection(wxFileCtrlEvent& event);
	
	wxDECLARE_EVENT_TABLE();
};

#endif
