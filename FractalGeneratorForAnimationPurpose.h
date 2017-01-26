#pragma once
#include <fstream>
#include <wx/gdicmn.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h> 
#include <wx/panel.h>

#include "Fractal2D.h"

enum dimension
{
	d2D = 0,
	d3D = 1
};

struct Position
{
	Position(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
	double x;
	double y;
	double z;
};

class FractalGeneratorForAnimationPurpose
{
public:
	FractalGeneratorForAnimationPurpose(wxString filepath, wxPanel * panel);
	~FractalGeneratorForAnimationPurpose();

	bool ReadDataFromTxtFile();
	Fractal2D ** GenerateFractalsForAnimationPurpose();

	wxSize GetBitmapSize();
	Fractal** GetFractals();
	int GetFractalNumber();
	int GetTemporaryFractalStatesNumber();

protected:
	wxFileInputStream input_stream;
	wxTextInputStream input_text_stream; 

	wxSize bitmapSize; 
	wxPanel * drawPanel;
	int fractalPixelsNumber; 
	dimension fractalDimension; 
	Position viewerPos; 
	int fractalNumber; 
	int transitionNumber;
	int temporaryFractalStatesNumber;
	int * temporaryFractalStatesNumberArray; 
	Fractal2D ** fractals;
};

