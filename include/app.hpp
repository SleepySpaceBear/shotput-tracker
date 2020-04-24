#ifndef APP_HPP
#define APP_HPP

#include "wx/app.h"

class App : public wxApp {
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;

	void LoadVideo(std::string& path);
private:
};

wxDECLARE_APP(App);

#endif