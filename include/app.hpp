#ifndef TRACKER_HPP
#define TRACKER_HPP

#include "wx/app.h"

class App : public wxApp {
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
private:
};

#endif