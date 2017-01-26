#include "FractalGeneratorForAnimationPurpose.h"
#include "Fractal2D.h"

/*
[rozmiar x bitmap],[rozmiar y bitmap],[ile iteracji],[typ:0 – 2D, 1 - 3D] 
[x_obserwatora][y_obserwatora][z_obserwatora] 
[ile fraktali bedziemy animowac min.2] 
[ilosc przeksztalcen dla pierwszego fraktala] 
[przeksztalcenie 1] 
.....
[przeksztalcenie n]
[ile klatek animacji do kolejnego fraktala] 
[ilosc przeksztalcen dla drugiego fraktala] 
[przeksztalcenie 1] 
.....
[przeksztalcenie n]
*/
FractalGeneratorForAnimationPurpose::FractalGeneratorForAnimationPurpose(wxString filepath, wxPanel * panel) :
	input_stream(filepath),
	input_text_stream(input_stream),
	bitmapSize(0, 0),
	drawPanel(panel),
	fractalPixelsNumber(0),
	fractalDimension(d2D),
	viewerPos(0, 0, 0),

	fractalNumber(0),
	fractals(nullptr),

	transitionNumber(0),

	temporaryFractalStatesNumber(0),
	temporaryFractalStatesNumberArray(nullptr)
{
	ReadDataFromTxtFile();
}


FractalGeneratorForAnimationPurpose::~FractalGeneratorForAnimationPurpose()
{
	if (this->fractals != nullptr)
	{
		for (int i = 0; i < this->fractalNumber; i++)
			delete this->fractals[i];
		delete[] this->fractals;
	}
	delete[] temporaryFractalStatesNumberArray;
}


bool FractalGeneratorForAnimationPurpose::ReadDataFromTxtFile()
{
	int dimension;
	this->input_text_stream.SetStringSeparators(" ,");

	this->input_text_stream
		>> this->bitmapSize.x
		>> this->bitmapSize.y
		>> this->fractalPixelsNumber
		>> dimension;

	this->fractalDimension = dimension == 0 ? d2D : d3D;

	this->input_text_stream
		>> this->viewerPos.x >> this->viewerPos.y >> this->viewerPos.z;

	this->input_text_stream
		>> this->fractalNumber;
	this->transitionNumber = this->fractalNumber - 1;

	this->fractals = new Fractal2D *[this->fractalNumber];
	for (int i = 0; i < this->fractalNumber; i++)
		fractals[i] = nullptr;


	int transformationNumber; 
	this->temporaryFractalStatesNumberArray = new int[this->transitionNumber];

	for (int j = 0; j < fractalNumber; j++)
	{

		this->input_text_stream >> transformationNumber;
		fractals[j] = new Fractal2D(this->fractalPixelsNumber, this->bitmapSize, transformationNumber);
		

		for (int i = 0; i < transformationNumber; i++) {
			fractals[j]->AddTransformation(this->input_text_stream, i);
		}

		if (j != fractalNumber - 1 ) {
			this->input_text_stream >> this->temporaryFractalStatesNumberArray[j];
			this->temporaryFractalStatesNumber+= this->temporaryFractalStatesNumberArray[j];
		}
	}

	return true;
}

Fractal2D ** FractalGeneratorForAnimationPurpose::GenerateFractalsForAnimationPurpose() {
	Fractal2D ** temporaryFractalStates = new Fractal2D*[this->temporaryFractalStatesNumber];

	int particularTransitionFractalStatesNumber = 0;
	int globalFractalStateIndex = 0;
	for (int i = 0; i < this->transitionNumber; i++)
	{
	    particularTransitionFractalStatesNumber = temporaryFractalStatesNumberArray[i];

		Fractal2D* fractal1 = this->fractals[i];
		Fractal2D* fractal2 = this->fractals[i + 1];

		int fractal1TransformationNumber = fractal1->GetTransformationNumber();
		int fractal2TransformationNumber = fractal2->GetTransformationNumber();

		int diffrence = fabs(fractal1TransformationNumber - fractal2TransformationNumber);

		AffineTransformationRates2D* newTransformation = new AffineTransformationRates2D();

		if (fractal1TransformationNumber > fractal2TransformationNumber) {
			for (int l = 0; l < diffrence; l++)
			{
				fractal2->AppendTransformation(newTransformation);
			}
		}
		else {
			for (int l = 0; l < diffrence; l++)
			{
				fractal1->AppendTransformation(newTransformation);
			}

		}
		int newTransformationsNumber = fractal1->GetTransformationNumber();
		AffineTransformationRates2D** transformationRatesForOneStep = new AffineTransformationRates2D*[newTransformationsNumber];
		for (int j = 0; j < newTransformationsNumber; j++)
		{
			double a_step = (fractal2->GetParticularTransformationRates(j)->a - fractal1->GetParticularTransformationRates(j)->a) / particularTransitionFractalStatesNumber;
			double b_step = (fractal2->GetParticularTransformationRates(j)->b - fractal1->GetParticularTransformationRates(j)->b) / particularTransitionFractalStatesNumber;
			double c_step = (fractal2->GetParticularTransformationRates(j)->c - fractal1->GetParticularTransformationRates(j)->c) / particularTransitionFractalStatesNumber;
			double d_step = (fractal2->GetParticularTransformationRates(j)->d - fractal1->GetParticularTransformationRates(j)->d) / particularTransitionFractalStatesNumber;
			double e_step = (fractal2->GetParticularTransformationRates(j)->e - fractal1->GetParticularTransformationRates(j)->e) / particularTransitionFractalStatesNumber;
			double f_step = (fractal2->GetParticularTransformationRates(j)->f - fractal1->GetParticularTransformationRates(j)->f) / particularTransitionFractalStatesNumber;

			transformationRatesForOneStep[j] = new AffineTransformationRates2D(
				a_step, 
				b_step, 
				c_step, 
				d_step, 
				e_step, 
				f_step, 1./newTransformationsNumber);
		}

		AffineTransformationRates2D** transformationRatesForTemporaryFractalState = new AffineTransformationRates2D*[newTransformationsNumber];
		for (int k = 0; k < particularTransitionFractalStatesNumber; k++)
		{
			for (int m = 0; m < newTransformationsNumber; m++)
			{
				AffineTransformationRates2D * t = fractal1->GetParticularTransformationRates(m);
				transformationRatesForTemporaryFractalState[m] = new AffineTransformationRates2D(t, transformationRatesForOneStep[m], k);
			}
		 	temporaryFractalStates[globalFractalStateIndex] = new Fractal2D(this->fractalPixelsNumber, this->bitmapSize, newTransformationsNumber, transformationRatesForTemporaryFractalState);
			globalFractalStateIndex++;
		}

	}
	return temporaryFractalStates;
}


wxSize FractalGeneratorForAnimationPurpose::GetBitmapSize()
{
	return this->bitmapSize;
}



int FractalGeneratorForAnimationPurpose::GetFractalNumber()
{
	return this->fractalNumber;
}

int FractalGeneratorForAnimationPurpose::GetTemporaryFractalStatesNumber() {
	return this->temporaryFractalStatesNumber;
}




