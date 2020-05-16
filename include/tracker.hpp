#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <thread>

#include "opencv2/opencv.hpp"

class Tracker {
public:
	Tracker() = default;
	~Tracker() = default;

	// finds the shotput in the frame and edits it accordingly
	void processFrame(cv::Mat& frame);
private:
	const static int s_shotputSize = 20;

	// previous video frame
	cv::Mat m_prevFrame;

	cv::Point findShotput(cv::Mat& frame);
	void drawCircle(const cv::Point& loc, cv::Mat& frame);
};

#endif