#include "ui.hpp"

class Test : public wxApp {
public:
	virtual bool OnInit() override;
private:
};

bool Test::OnInit() {
	UI *frame = new UI("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(Test);