#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <thread>

#include "opencv2/opencv.hpp"
#include "video.hpp"

class Tracker {
public:
	Tracker() = default;
	~Tracker() = default;

	// finds the shotput in the frame and edits it accordingly
	void processFrame(cv::Mat& frame);
private:
	// previous video frame
	cv::Mat m_prevFrame;
};

#endif