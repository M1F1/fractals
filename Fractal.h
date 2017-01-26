#pragma once
#include <wx/gdicmn.h>
#include <wx/txtstrm.h> // text stream file
#include <wx/panel.h>

class Fractal
{
public:

	Fractal(int pixelsNumber, wxSize bitmap, int transformationNumber);
	virtual ~Fractal();

	virtual void AddTransformation(wxTextInputStream & fstr, int i) = 0;
	virtual int GetTransformationNumber();


	virtual void GenerateBitmap(wxString filename, wxPanel * drawPanel) = 0;

protected:

	int pixelsNumber; 
	wxSize bitmapSize; 
	int transformationNumber; 
};

