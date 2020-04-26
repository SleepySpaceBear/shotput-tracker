#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <vector>
#include "wx/image.h"
#include "opencv2/opencv.hpp"

class Video {
public:
	Video() = default;

	// opens the file at the given path
	bool open(std::string& path);

	// returns the number of frames in the video
	int getNumFrames() const;
	// gets a frame in a format that can be displayed wxWidgets
	wxImage getDisplayFrame(int frameNum) const;
	// gets the frame in a format that can be processed by OpenCV
	cv::Mat getProcFrame(int frameNum) const;
	// returned whether this class currently holds a loaded video
	bool isLoaded() const;
	// gets the width of the video
	int getWidth() const;
	// gets the height of the video
	int getHeight() const;
private:
	std::vector<cv::Mat> m_frames;
	int m_height = -1;
	int m_width = -1;
};

#endif