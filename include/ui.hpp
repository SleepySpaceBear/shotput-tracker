#ifndef UI_HPP
#define UI_HPP
#include "wx/wx.h"

class App;

class UI : public wxFrame {
public:
	UI(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
#endif