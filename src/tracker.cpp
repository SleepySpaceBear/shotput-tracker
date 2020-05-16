#include <opencv2/imgproc.hpp>
#include "tracker.hpp"

const static cv::Scalar g_white{ 255, 255, 255 };
const static cv::Scalar g_grey{ 128, 128, 128 };
const static cv::Scalar g_black{ 0, 0, 0 };
const static float g_threshold = 0.2;

void Tracker::processFrame(cv::Mat& frame) {
	cv::Point loc = findShotput(frame);
	
	if (loc.x != -1 && loc.y != -1) {
		drawCircle(loc, frame);
	}
}

cv::Point Tracker::findShotput(cv::Mat& frame) {
	// get the greyscale frame
	cv::Mat greyscale;
	cv::cvtColor(frame, greyscale, cv::COLOR_BGR2GRAY);

	// set-up our template and mask for finding shotputs
	// it's literally just a grey circle
	cv::Mat templ(s_shotputSize, s_shotputSize, greyscale.type(), g_grey);

	cv::Mat mask(s_shotputSize, s_shotputSize, greyscale.type(), g_grey);
	circle(mask, { s_shotputSize / 2, s_shotputSize }, s_shotputSize / 2, g_white, cv::FILLED);

	cv::Mat res(frame.rows - s_shotputSize + 1, frame.cols - s_shotputSize + 1, frame.type());
	cv::matchTemplate(greyscale, templ, res, cv::TM_SQDIFF, mask);
	cv::normalize(res, res, 0, 1, cv::NORM_MINMAX, -1);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;

	cv::minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);

	if (minVal < g_threshold) {
		return minLoc;
	}
	else {
		// return an invalid point
		return cv::Point{ -1, -1 };
	}
}

void Tracker::drawCircle(const cv::Point& loc, cv::Mat& frame) {
	cv::circle(frame, { loc.x + s_shotputSize / 2, loc.y + s_shotputSize / 2 }, s_shotputSize + 2, g_white, 2);
}
