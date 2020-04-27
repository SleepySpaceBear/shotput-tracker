#include "videoview.hpp"

#include "wx/time.h"

VideoView::VideoView(wxWindow* parent, Video* video) : 
	wxPanel(parent, wxID_ANY, wxDefaultPosition, { video->getWidth(), video->getHeight() }), m_pVideo(video) {
}


void VideoView::onPaint(wxPaintEvent & event) {
	wxPaintDC dc(this);
	
	if (staleFrame()) {
		updateCurFrame();
	}
	
	drawFrame(dc);
}

void VideoView::onIdle(wxIdleEvent& event) {
	if (staleFrame()) {
		wxClientDC dc(this);
		updateCurFrame();
		drawFrame(dc);
	}
}

void VideoView::updateCurFrame() {

	m_lastFrameTime = wxGetLocalTimeMillis();
	m_curFrameNum++;

	if (m_pVideo->getNumFrames() <= m_curFrameNum) {
		m_curFrameNum = 0;
	}

	m_curFrame = m_pVideo->getDisplayFrame(m_curFrameNum);
}

void VideoView::drawFrame(wxDC & dc) {
	if (m_pVideo->isLoaded()) {
		PrepareDC(dc);
		// make sure the panel is the right size
		SetSize(m_curFrame.GetWidth(), m_curFrame.GetHeight());
		SetVirtualSize(m_curFrame.GetWidth(), m_curFrame.GetHeight());
		
		if (dc.CanDrawBitmap()) {
			dc.DrawBitmap(m_curFrame, 0, 0);
		}
	}
}

bool VideoView::staleFrame() const {
	return ((wxGetLocalTimeMillis().GetValue() - m_lastFrameTime.GetValue()) / 1000.0) > (1.0 / m_pVideo->getFramerate());
}


wxBEGIN_EVENT_TABLE(VideoView, wxPanel)
EVT_PAINT(VideoView::onPaint)
EVT_IDLE(VideoView::onIdle)
wxEND_EVENT_TABLE();