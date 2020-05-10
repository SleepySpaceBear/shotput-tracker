#include "video.hpp"

void VideoBuffer::setWidth(int width) {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	m_nWidth.store(width);
}

void VideoBuffer::setHeight(int height) {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	m_nHeight.store(height);
}

void VideoBuffer::setFramerate(double framerate) {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	m_dFramerate.store(framerate);
}

void VideoBuffer::addFrame(const wxBitmap& frame) {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	m_vecFrames.push_back(frame);
}

int VideoBuffer::getNumFrames() const {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	return m_vecFrames.size();
}

wxBitmap VideoBuffer::getNextFrame() const {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	wxBitmap temp = std::move(m_vecFrames.front());
	m_vecFrames.erase(m_vecFrames.begin());
	return temp;
}

int VideoBuffer::getWidth() const {
	return m_nWidth.load();
}

int VideoBuffer::getHeight() const {
	return m_nHeight.load();
}

double VideoBuffer::getFramerate() const {
	return m_dFramerate.load();
}

bool VideoBuffer::hasNextFrame() const {
	std::unique_lock<std::mutex> lk{ m_mutAccess };
	return !m_vecFrames.empty();
}