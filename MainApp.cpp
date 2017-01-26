#include "MainApp.h"
#include "MainFrame.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	MainFrame* dialog = new MainFrame(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);
	return true;
}

int MainApp::OnExit()
{
	return 0;
}
