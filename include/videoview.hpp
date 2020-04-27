#ifndef VIDEOVIEW_HPP
#define VIDEOVIEW_HPP

#include "video.hpp"
#include "wx/wx.h"

class VideoView : public wxPanel {
public:
	VideoView(wxWindow* parent, Video* video);

private:
	// pointer to the video that this is drawing
	Video* m_pVideo;
	// the last time a frame was drawn
	wxMilliClock_t m_lastFrameTime;
	// the current frmae
	wxBitmap m_curFrame;
	// the current frame number
	int m_curFrameNum = 0;

	// callback function for paint event
	void onPaint(wxPaintEvent& event);

	// callbakc function for idling
	void onIdle(wxIdleEvent& event);

	// implementation of drawFrame
	void _drawFrame(wxDC& dc);

	// returns whether the current frame is "stale"
	bool staleFrame() const;

	wxDECLARE_EVENT_TABLE();
};

#endif