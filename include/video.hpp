#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <atomic>
#include <vector>
#include <memory>
#include <thread>
#include "wx/bitmap.h"
#include "opencv2/opencv.hpp"


class Video {
public:
	enum class FrameState {
		NOFRAME = -1,
		UNPROCESSED = 0,
		PROCESSED,
		CONVERTED
	};

	struct Frame {
		mutable std::mutex mutStateChange;
		mutable std::condition_variable cvStateChange;
		cv::Mat mat;
		std::atomic<FrameState> state = FrameState::NOFRAME;
	};

	Video();
	~Video();

	// opens the file at the given path
	bool open(std::string& path);

	// returns the number of frames in the video
	int getNumFrames() const;
	// gets a frame in a format that can be displayed wxWidgets
	wxBitmap getDisplayFrame(int frameNum) const;
	// gets the frame in a format that can be processed by OpenCV
	Frame& getFrame();
	// returned whether this class currently holds a loaded video
	bool isLoaded() const;
	// gets the width of the video
	int getWidth() const;
	// gets the height of the video
	int getHeight() const;
	// gets the framerate of the video
	double getFramerate() const;

private:
	cv::VideoCapture m_vidCapture;
	std::vector<wxBitmap> m_vecBitmaps;
	std::thread m_threadFrameConverter;
	Frame m_curFrame;

	double m_dFramerate;
	int m_nHeight = -1;
	int m_nWidth = -1;
	std::atomic<bool> m_alive = true;

	// function for doing the behind the scenes work
	void work();
	void loadFrame();
	void convertFrame();
};

class VideoProcessor {

};

#endif