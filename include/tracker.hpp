#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <thread>

#include "opencv2/opencv.hpp"
#include "video.hpp"

class Tracker {
public:
	Tracker();
	~Tracker();

	void setVideo(Video* video);
private:
	std::thread m_threadFrameProcessor;
	Video* m_video = NULL;
	cv::Mat m_prevFrame;
	std::atomic<bool> m_alive = true;

	// function for processing the video
	void processVideo();

	// function for processing the current video frame
	// essentially a wrapper for _processFrame
	void processFrame();
	// helper function for processFrame that actually does the OpenCV work
	void _processFrame(cv::Mat& frame);
};

#endif