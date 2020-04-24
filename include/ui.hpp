#ifndef UI_HPP
#define UI_HPP
#include "wx/wx.h"

/*
 * Unscoped enum for UI events 
*/
enum : int { EV_LOAD_VIDEO = 0, NUM_EVENTS };

class App;

class UI : public wxFrame {
public:
	UI(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnLoadVideo(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
#endif