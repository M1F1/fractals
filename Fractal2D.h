#pragma once
#include "Fractal.h"

struct AffineTransformationRates2D
{
	AffineTransformationRates2D()
	{
		this->a = 0;
		this->b = 0;
		this->c = 0;
		this->d = 0;
		this->e = 0;
		this->f = 0;
		this->probability = 0;
	}


	AffineTransformationRates2D(double a, double b, double c, double d, double e, double f, double probability)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
		this->probability = probability;
	}


	AffineTransformationRates2D(AffineTransformationRates2D * t, AffineTransformationRates2D* stepTransformationRates, int step) 
	{
		this->a = t->a + stepTransformationRates->a * step;
		this->b = t->b + stepTransformationRates->b * step;
		this->c = t->c + stepTransformationRates->c * step;
		this->d = t->d + stepTransformationRates->d * step;
		this->e = t->e + stepTransformationRates->e * step;
		this->f = t->f + stepTransformationRates->f * step;
		this->probability = stepTransformationRates->probability;
	}

	double a, b, e, c, d, f;
	double probability;
};


class Fractal2D : public Fractal
{
public:

	Fractal2D(int iter, wxSize bitmp, int nTrans);
	Fractal2D::Fractal2D(int iter, wxSize bitmp, int nTrans, AffineTransformationRates2D** transformationsRates);
	~Fractal2D();

	virtual void AddTransformation(wxTextInputStream & fstr, int i) override;
	virtual void AppendTransformation(AffineTransformationRates2D * newTransformation);
	virtual void GenerateBitmap(wxString filename, wxPanel * drawPanel) override;
	AffineTransformationRates2D* GetParticularTransformationRates(int i);

private:

	AffineTransformationRates2D ** transformationsRates;

};

