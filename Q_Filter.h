#pragma once
//#include "Q_Filter.h"
#include "..\Q_Vector.h"
#include  "GlobalOptions.h"

struct Filter
{
	int lastX = 0;
	int lastY = 0;
	double kReduce;
	Vector delta;
	RGBQUAD** screen;
	RGBQUAD* finalDC;
	Vector size;
	RGBQUAD* tempScreen;
	double totalProgress;
	double currentProgress = 0;
	Vector screenSize;
	bool confirmBrightness = false;
	//bool (*reCount)(Filter& filter, int screenSize, bool confirmBrightness, double Brightness, double IncomeBrightness);
	RGBQUAD(*algorithm)(RGBQUAD pixel, double Brightness, double IncomeBrightness);

	Filter(RGBQUAD** _screen, Vector _size, RGBQUAD* _finalDC, RGBQUAD* _tempScreen, Vector _screenSize, RGBQUAD(*_algorithm)(RGBQUAD pixel, double Brightness, double IncomeBrightness) = NULL, double _kReduce = 10) :
		screen(_screen),
		size(_size),
		kReduce(_kReduce),
		finalDC(_finalDC),
		tempScreen(_tempScreen),
		algorithm (_algorithm),
		screenSize (_screenSize)
	{
        if (kReduce == 0) printf ("ERROR in filters");
		delta = size / kReduce;
		if (delta > 0) totalProgress = (size.x / delta.x) * (size.y / delta.y);
        else totalProgress = 0;
	}

	bool reCount(bool& nonConfirm, double Brightness, double IncomeBrightness);
	//void reStartCount();
	void confirm(HDC dest, HDC source, bool& nonConfirm);
    void init (RGBQUAD** _screen, Vector _size, RGBQUAD* _finalDC, RGBQUAD* _tempScreen, Vector _screenSize, RGBQUAD(*_algorithm)(RGBQUAD pixel, double Brightness, double IncomeBrightness) = NULL, double _kReduce = 10);

};


void Filter::init (RGBQUAD** _screen, Vector _size, RGBQUAD* _finalDC, RGBQUAD* _tempScreen, Vector _screenSize, RGBQUAD(*_algorithm)(RGBQUAD pixel, double Brightness, double IncomeBrightness) /* = NULL*/, double _kReduce /* = 10*/)
{
    screen = _screen;
	size = size;
	kReduce = kReduce;
	finalDC = finalDC;
	tempScreen = tempScreen;
	algorithm = algorithm;
	screenSize = screenSize;

    if (kReduce == 0) printf ("ERROR in filters");
	delta = size / kReduce;
	if (delta > 0) totalProgress = (size.x / delta.x) * (size.y / delta.y);
    else totalProgress = 0;
}



bool Filter::reCount(bool& nonConfirm, double Brightness, double IncomeBrightness)
{
	//printf("%lf %lf\n", Brightness, IncomeBrightness);
    if (!screen) return 1;

	nonConfirm = true;
	for (int x = 0; x < _app->systemSettings->DCMAXSIZE; x++)
	{
		for (int y = 0; y < _app->systemSettings->DCMAXSIZE; y++)
		{
			int pixelPos = (int) (_app->systemSettings->DCMAXSIZE - y) * ((int)(_app->systemSettings->DCMAXSIZE - 1)) + x;
			RGBQUAD pixel = (*screen)[pixelPos];

			assert(algorithm);
			pixel = algorithm(pixel, Brightness, IncomeBrightness);
			/*
			double kOfBrightness = (double)((255 - Brightness) - (255 - IncomeBrightness)) / (255.0); 
			double bOfBrightness = 255 - IncomeBrightness;	

			//if (pixel.rgbRed >= 128) _getch();
			pixel.rgbRed = pixel.rgbRed * kOfBrightness + bOfBrightness;
			pixel.rgbGreen = pixel.rgbGreen * kOfBrightness + bOfBrightness;
			pixel.rgbBlue = pixel.rgbBlue * kOfBrightness + bOfBrightness;
			 */
			
			tempScreen[pixelPos] = pixel;
		}
	}


	return true; //дальше идет отклбюченный фоновый расчет фильтра
	lastY += delta.y;
	currentProgress++;
	if (lastY >= size.y)
	{
		lastY = 0;
		lastX += delta.x;
	}
	if (lastX >= size.y)
	{
		lastY = 0;
		lastX = 0;
		currentProgress = 0;
		return true;//reDraw
	}
	return false;
}

void Filter::confirm(HDC dest, HDC source, bool& nonConfirm)
{

	

}