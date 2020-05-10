#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <atomic>
#include <vector>
#include <thread>
#include "wx/bitmap.h"
#include "opencv2/opencv.hpp"


class VideoBuffer {
public:
	VideoBuffer() = default;
	~VideoBuffer() = default;
	
	// setters
	
	// sets video width
	void setWidth(int width);
	// sets video height
	void setHeight(int height);
	// sets video framerate
	void setFramerate(double framerate);

	// adds a frame to the video
	void addFrame(const wxBitmap& bitmap);

	// getters

	// returns the number of frames in the video
	int getNumFrames() const;
	// gets the next available frame
	wxBitmap getNextFrame() const;
	// gets the width of the video
	int getWidth() const;
	// gets the height of the video
	int getHeight() const;
	// gets the framerate of the video
	double getFramerate() const;
	// gets whether there is a another frame
	bool hasNextFrame() const;

private:
	mutable std::vector<wxBitmap> m_vecFrames;
	mutable std::mutex m_mutAccess;

	std::atomic<double> m_dFramerate = 0;
	std::atomic<int> m_nHeight = -1;
	std::atomic<int> m_nWidth = -1;
};

#endif