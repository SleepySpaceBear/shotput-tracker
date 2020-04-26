#ifndef UI_HPP
#define UI_HPP
#include "wx/wx.h"

/*
 * Unscoped enum for UI events 
 */
enum : int { EV_LOAD_VIDEO = 0, NUM_EVENTS };

/*
 * A class representing the main UI for this program.
 * It calls upon the App class as needed through the wxGetApp function
 */
class UI : public wxFrame {
public:
	// Public constructor
	UI(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	// callback function for selecting the "Load Video" menu option
	void OnLoadVideo(wxCommandEvent& event);
	// callback function for selecting the "About" menu option
	void OnAbout(wxCommandEvent& event);
	// callback function for closing the window
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
#endif