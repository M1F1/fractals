///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MAINFRAME 1000
#define wxID_DRAWPANEL 1001
#define wxID_READFILE 1002

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////

#include "FractalGeneratorForAnimationPurpose.h"
class MainFrame : public wxFrame
{
private:

protected:
	wxPanel* drawPanel;
	wxButton* readFileButton;
	wxButton* animateFractalButton;
	wxTimer mainTimer;

	wxImage fractalImage;
	wxBitmap  myBitMap;
	FractalGeneratorForAnimationPurpose* fractalGenerator;

	// Virtual event handlers, overide them in your derived class
	virtual void readFileButtonOnLeftUp(wxMouseEvent& event);
	virtual void animateFractalButtonOnLeftUp(wxMouseEvent& event);

public:

	MainFrame(wxWindow* parent, wxWindowID id = wxID_MAINFRAME, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(360, 300), long style = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX) | wxICONIZE | wxMINIMIZE | wxSYSTEM_MENU | wxTAB_TRAVERSAL);

	~MainFrame();

protected:
	/* Adjust size of the drawPanle to size given in file */
	void AdjustFrameSize(const wxSize bitmapSize);
};