#ifndef APP_HPP
#define APP_HPP

#include "wx/app.h"

class App : public wxApp {
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
private:
};

wxDECLARE_APP(App);

#endif