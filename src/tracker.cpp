#include "tracker.hpp"

Tracker::Tracker() {
	m_threadFrameProcessor = std::move(std::thread([this] { this->processVideo(); }));
}

Tracker::~Tracker() {
	m_alive.store(false);
	m_threadFrameProcessor.join();
}

void Tracker::setVideo(Video* video) {
	m_video = video;
}

void Tracker::processVideo() {
	while (m_alive) {
		if (m_video != nullptr) {
			processFrame();

			// additional work goes here
		}
	}
}

void Tracker::processFrame() {
	Video::Frame& frame = m_video->getFrame();
	{
		std::unique_lock<std::mutex> lk{ frame.mutStateChange };

		// wait for the current frame to be ready for processing
		if (frame.state != Video::FrameState::UNPROCESSED) {
			frame.cvStateChange.wait(lk, [&frame] { return frame.state == Video::FrameState::UNPROCESSED; });
		}

		_processFrame(frame.mat);
		m_prevFrame = frame.mat.clone();
		frame.state = Video::FrameState::PROCESSED;
	}
	frame.cvStateChange.notify_all();
}

void Tracker::_processFrame(cv::Mat& frame) {
	// TODO: Sam process the frame here
	// You got m_prevFrame and frame 
}