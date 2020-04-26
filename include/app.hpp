#ifndef APP_HPP
#define APP_HPP

#include "wx/app.h"
#include "opencv2/opencv.hpp"

class App : public wxApp {
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;

	bool LoadVideo(std::string& path);
	cv::VideoCapture& GetVideo();
private:
	cv::VideoCapture m_video;
};

wxDECLARE_APP(App);

#endif