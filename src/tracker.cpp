#include "tracker.hpp"

#include <opencv2/imgproc.hpp>
#include "constants.hpp"

const static cv::Scalar g_white{ 255, 255, 255 };
const static cv::Scalar g_grey{ 128, 128, 128 };
const static cv::Scalar g_black{ 0, 0, 0 };
const static float g_threshold = 0.2;

void Tracker::processFrame(cv::Mat& frame) {
	cv::resize(frame, frame, { frame.cols / SPT_VID_SCALE_FACTOR , frame.rows / SPT_VID_SCALE_FACTOR });

	cv::Point loc = findShotput(frame);
	
	if (loc.x != -1 && loc.y != -1) {
		drawCircle(loc, frame);
	}
}

cv::Point Tracker::findShotput(cv::Mat& frame) {
	// get the greyscale frame
	cv::Mat greyscale;
	cv::cvtColor(frame, greyscale, cv::COLOR_BGR2GRAY);

	cv::Point loc{ -1, -1 };


	return loc;
}

void Tracker::drawCircle(const cv::Point& loc, cv::Mat& frame) {
	cv::circle(frame, { loc.x + s_shotputSize / 2, loc.y + s_shotputSize / 2 }, s_shotputSize + 2, g_white, 2);
}
