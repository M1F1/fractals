#include "Fractal2D.h"
#include <wx/image.h>

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <random>



Fractal2D::Fractal2D(int iter, wxSize bitmp, int nTrans) : 
	Fractal(iter, bitmp, nTrans),
	transformationsRates(new AffineTransformationRates2D*[this->transformationNumber])
{
	for (int i = 0; i < this->transformationNumber; i++)
	{
		this->transformationsRates[i] = new AffineTransformationRates2D();
	}
}


Fractal2D::Fractal2D(int iter, wxSize bitmp, int nTrans, AffineTransformationRates2D** transformationsRates ) : 
	Fractal(iter, bitmp, nTrans),
	transformationsRates(new AffineTransformationRates2D*[this->transformationNumber])
{
	for (int i = 0; i < this->transformationNumber; i++)
	{
		this->transformationsRates[i] = transformationsRates[i];
	}
}


Fractal2D::~Fractal2D()
{
	for (int i = 0; i < this->transformationNumber; i++)
	{
		delete this->transformationsRates[i];
	}
	delete[] this->transformationsRates;
}


void Fractal2D::AddTransformation(wxTextInputStream & fstr, int i)
{
	fstr >> this->transformationsRates[i]->a
		>> this->transformationsRates[i]->b
		>> this->transformationsRates[i]->c
		>> this->transformationsRates[i]->d
		>> this->transformationsRates[i]->e
		>> this->transformationsRates[i]->f;

	this->transformationsRates[i]->probability = 1. / this->transformationNumber;
}


void Fractal2D::AppendTransformation(AffineTransformationRates2D* newTransformation)
{
	this->transformationNumber += 1;
	AffineTransformationRates2D** newTransformations = new AffineTransformationRates2D*[this->transformationNumber];
	for (int i = 0; i < transformationNumber - 1; i++)
	{
		newTransformations[i] = this->transformationsRates[i];
		//newTransformations[i]->probability = 1. / this->transformationNumber;
	}
	newTransformations[this->transformationNumber - 1] = newTransformation;
	newTransformations[this->transformationNumber - 1]->probability = 0.;
	delete[] this->transformationsRates;
	this->transformationsRates = newTransformations;
}


AffineTransformationRates2D* Fractal2D::GetParticularTransformationRates(int i) {
	if (i < transformationNumber) {
		return this->transformationsRates[i];
	}
	return nullptr;
}


void Fractal2D::GenerateBitmap(wxString filename, wxPanel * drawPanel)
{
	wxImage fractalImage(this->bitmapSize);
	wxClientDC * cDC = new wxClientDC(drawPanel);
	wxBufferedDC * bDC = new wxBufferedDC(cDC);
	bDC->Clear();
	bDC->SetPen(wxPen(wxColor(0, 0, 0)));

	// ******** WHY WHAT ********

	int strechFactor = this->bitmapSize.x > this->bitmapSize.y ? this->bitmapSize.y : this->bitmapSize.x;

	wxCoord x = 0,  y  = 0;
	double x1 = 0., y1 = 0.;
	double x2 = 0., y2 = 0.;

	int thresholdsNumber = transformationNumber + 1;
	double * thresholds = new double[thresholdsNumber];
	thresholds[0] = 0.;
	thresholds[thresholdsNumber - 1] = 1.;
	for (int i = 1; i < thresholdsNumber - 1; i++)
	{
		thresholds[i] = this->transformationsRates[i - 1]->probability * double(i);
	}

    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	double random_number; 

	for (int i = 0; i < pixelsNumber; i++)
	{
		random_number = dis(gen);
		for (int j = 0; j < thresholdsNumber - 1; j++)
		{
			if (random_number >= thresholds[j] && random_number <= thresholds[j + 1])
			{
				x2 = this->transformationsRates[j]->a * x1 + this->transformationsRates[j]->b * y1 + this->transformationsRates[j]->e;
				y2 = this->transformationsRates[j]->c * x1 + this->transformationsRates[j]->d * y1 + this->transformationsRates[j]->f;
				x1 = x2;
				y1 = y2;
				x = static_cast<wxCoord>(x1 * this->bitmapSize.x);
				y = static_cast<wxCoord>(y1 * this->bitmapSize.y);

				bDC->DrawPoint(x, y);
				break;
			}
		}
	}

	wxBitmap fractalBitmap = bDC->GetAsBitmap();
	fractalImage = fractalBitmap.ConvertToImage();
	fractalImage.SaveFile(filename, wxBITMAP_TYPE_BMP);

	delete[] thresholds;
	delete bDC;
	delete cDC;
}