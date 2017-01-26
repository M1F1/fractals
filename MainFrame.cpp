///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

#include <wx/filedlg.h>

#include "FractalGeneratorForAnimationPurpose.h"
#include "Fractal.h"
///////////////////////////////////////////////////////////////////////////
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <sstream>
#include <windows.h>
MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(-1, -1), wxDefaultSize);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer(wxVERTICAL);

	drawPanel = new wxPanel(this, wxID_DRAWPANEL, wxDefaultPosition, wxSize(300, 400), wxTAB_TRAVERSAL);
	panelSizer->Add(drawPanel, 1, wxEXPAND | wxALL, 5);


	mainSizer->Add(panelSizer, 1, wxEXPAND, 5);

	wxBoxSizer* controlSizer;
	controlSizer = new wxBoxSizer(wxVERTICAL);

	readFileButton = new wxButton(this, wxID_READFILE, wxT("Read File"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(readFileButton, 0, wxALL, 5);

	animateFractalButton = new wxButton(this, wxID_READFILE, wxT("Animate"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(animateFractalButton, 0, wxALL, 5);
	animateFractalButton->Disable();


	mainSizer->Add(controlSizer, 0, wxALIGN_LEFT | wxALL, 5);


	this->SetSizer(mainSizer);
	this->Layout();
	mainTimer.SetOwner(this, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	readFileButton->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::readFileButtonOnLeftUp), NULL, this);
	animateFractalButton->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::animateFractalButtonOnLeftUp), NULL, this);
}

MainFrame::~MainFrame()
{
}
// TODO what that function do ? 
void MainFrame::AdjustFrameSize(const wxSize bitmapSize)
{
	wxSize windowSize = this->GetSize();
	wxSize panelSize = this->drawPanel->GetSize();
	this->SetSize(bitmapSize);

	while (panelSize.x < bitmapSize.x)
	{
		windowSize = this->GetSize();
		windowSize.x++;
		this->SetSize(windowSize);
		panelSize = this->drawPanel->GetSize();
		panelSize.x++;
		this->drawPanel->SetSize(panelSize);
	}
	//expand y direction
	while (panelSize.y < bitmapSize.y)
	{
		windowSize = this->GetSize();
		windowSize.y++;
		this->SetSize(windowSize);
		panelSize = this->drawPanel->GetSize();
		panelSize.y++;
		this->drawPanel->SetSize(panelSize);
	}
	this->readFileButton->SetPosition(wxDefaultPosition);
	this->animateFractalButton->SetPosition(wxDefaultPosition);
	Refresh();

}

void MainFrame::readFileButtonOnLeftUp(wxMouseEvent& event) 
{
	wxFileDialog openFileDialog(this, _("Open text file"), "", "",
			"text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL) return;      

	fractalGenerator = new  FractalGeneratorForAnimationPurpose(openFileDialog.GetPath(), drawPanel);
	Fractal2D** allFractalStates = fractalGenerator->GenerateFractalsForAnimationPurpose();

	this->AdjustFrameSize(fractalGenerator->GetBitmapSize());

	for (int i = 0; i < fractalGenerator->GetTemporaryFractalStatesNumber(); i++)
	{
		wxString name = "";
		name << i + 1 << ".bmp";
		allFractalStates[i]->GenerateBitmap(name, drawPanel);
	}
	animateFractalButton->Enable();
}
void MainFrame::animateFractalButtonOnLeftUp(wxMouseEvent & event)
{
	wxInitAllImageHandlers(); 
	
	
	int  iternum = fractalGenerator->GetTemporaryFractalStatesNumber();
	std::ostringstream stream;
	for (int i = 1; i <iternum + 1 ; i++)
	{
		this->fractalImage.AddHandler(new wxBMPHandler);
		this->drawPanel->SetSize(fractalImage.GetSize());
	    wxClientDC* cDC = new wxClientDC(this->drawPanel);
		wxBufferedDC * bDC = new wxBufferedDC(cDC);
		bDC->Clear();

		stream << i << ".bmp";
		this->fractalImage.LoadFile(stream.str(), wxBITMAP_TYPE_BMP);
		stream.str("");

		myBitMap = wxBitmap( fractalImage);
		bDC->DrawBitmap(myBitMap, 0, 0, false);
		Sleep(10);

		bDC->UnMask();
	}
	event.Skip();
	Refresh();
	return;

}
