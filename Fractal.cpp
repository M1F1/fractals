#include "Fractal.h"


Fractal::Fractal(int pixelsNumber, wxSize bitmap, int transformationNumbers) :
	pixelsNumber(pixelsNumber),
	bitmapSize(bitmap),
	transformationNumber(transformationNumbers)
{}

Fractal::~Fractal(){}

int Fractal::GetTransformationNumber()
{
	return transformationNumber;
}


