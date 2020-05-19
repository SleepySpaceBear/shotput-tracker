#ifndef TRACKER_HPP
#define TRACKER_HPP

// how many templates we have
// allows this to be overrode
#ifndef SAMPLE_COUNTS
#define SAMPLE_COUNTS 24
#endif

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



	typedef struct matched_location
	{
		int has_changed = -1;
		int detected_size = -1;
		int x_center = -1;
		int y_center = -1;
		int prev_x_center = -1;
		int prev_y_center = -1;
		cv::Scalar average_center_color = cv::Scalar(-1, -1, -1);
		// agree_score is the count of matching matched_locations nearby. The higher, the better
		int agree_score = -1;
		int plausible_color = -1;

	}a_location;

	struct all_matched_locations
	{
		a_location location[SAMPLE_COUNTS];
	};
};

#endif