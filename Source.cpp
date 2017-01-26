#include <wx/wx.h>
#include <wx/frame.h>

class my_first_app : public wxApp
{
public:
	bool OnInit()
	{
		wxFrame * window = new wxFrame(NULL, -1, "hi there");
		window->Show();
		return true;
	}
};

IMPLEMENT_APP(my_first_app);