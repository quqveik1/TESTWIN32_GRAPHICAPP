#pragma once
#include "TXLib.h"
#include "DrawBibliothek.h"
#include "LoadManager.h"

struct Slider : Manager 
{
	Window arrow1;
	Window arrow2;
	Window sliderQuadrate;
	double *num;
	double minNum;
	double maxNum;
	double kScale;
	bool horizontalMode;
	double axis;
	Vector cursorStartPosition;
	int tempNum;
	double quadrateScale;
	bool isWhite;
    CLoadManager* loadManager = NULL;

	Slider (AbstractAppData* _app, Rect _mainRect, double *_num, double _quadrateScale, int _minNum = 0, int _maxNum = 10, bool _horizontalMode = true, bool _isWhite = false) :
		Manager (_app, _mainRect, TX_BLACK),
		arrow1 (_app, {}, TX_RED),
		arrow2 (_app, {}, TX_RED),
		num (_num),
		minNum (_minNum),
		maxNum (_maxNum),
		horizontalMode (_horizontalMode),
		cursorStartPosition ({}),
		sliderQuadrate (_app, {}, TX_WHITE),
		tempNum (0),
		quadrateScale (_quadrateScale),
		isWhite (_isWhite),
        loadManager (_app->loadManager)
	{
		if (isWhite)
		{
			color = TX_WHITE;
		}
		arrow1.manager = this;
		arrow2.manager = this;
		sliderQuadrate.manager = this;

		if (horizontalMode)
		{
			arrow1.rect.pos.x = 0;
			arrow1.rect.pos.y = 0;
			arrow1.rect.finishPos.x = (1) * (rect.getSize ().y);
			arrow1.rect.finishPos.y = rect.getSize ().y;
			arrow1.originalRect = arrow1.rect;
			//compressImage (arrow1.dc, {arrow1.rect.getSize().x, arrow1.rect.getSize().y}, LoadManager.loadImage ("arrow1Hor.bmp"), {13, 17});
			app->compressImage (arrow1.dc, { arrow1.rect.getSize().x, arrow1.rect.getSize().y }, loadManager->loadImage("arrow1Hor.bmp"), {13, 17});

			if (isWhite) 
			{
				txDeleteDC (arrow1.dc);
                app->compressImage(arrow1.dc, {arrow1.rect.getSize().x, arrow1.rect.getSize().y}, loadManager->loadImage ("arrow1WhiteHor.bmp"), {16, 16});
			}


			arrow2.rect.pos.x = rect.getSize ().x - (1) * rect.getSize ().y;
			arrow2.rect.pos.y = 0;
			arrow2.rect.finishPos.x = rect.getSize ().x;
			arrow2.rect.finishPos.y = rect.getSize ().y;
			arrow2.originalRect = arrow2.rect;
            app->compressImage(arrow2.dc, {arrow2.rect.getSize().x, arrow2.rect.getSize().y}, loadManager->loadImage ("arrow2Hor.bmp"), {13, 17});
			if (isWhite) 
			{
				txDeleteDC (arrow2.dc);
                app->compressImage(arrow2.dc, {arrow2.rect.getSize().x, arrow2.rect.getSize().y}, loadManager->loadImage ("arrow2WhiteHor.bmp"), {16, 16});
                //printBlt (loadManager->loadImage ("arrow2WhiteHor.bmp"));
			}
		}
		else
		{
			arrow1.rect.pos.x = 0;
			arrow1.rect.pos.y = 0;
			arrow1.rect.finishPos.x = rect.getSize().x;
			arrow1.rect.finishPos.y = (1) * arrow1.rect.getSize().x;
			arrow1.originalRect = arrow1.rect;
			if (!isWhite) app->compressImage(arrow1.dc, {arrow1.rect.getSize().x, arrow1.rect.getSize().y}, loadManager->loadImage ("arrow1.bmp"), {17, 13});
			if (isWhite) 
			{
                app->compressImage(arrow1.dc, {arrow1.rect.getSize().x, arrow1.rect.getSize().y}, loadManager->loadImage ("arrow1WhiteVert.bmp"), {16, 16});
			}

			arrow2.rect.pos.x = 0;
			arrow2.rect.pos.y = rect.getSize().y - (1) * arrow1.rect.getSize().x;
			arrow2.rect.finishPos.x = rect.getSize().x;
			arrow2.rect.finishPos.y = rect.getSize().y;
			arrow2.originalRect = arrow2.rect;
			if (!isWhite) app->compressImage(arrow2.dc, {arrow2.rect.getSize().x, arrow2.rect.getSize().y}, loadManager->loadImage ("arrow2.bmp"), {17, 13});
			if (isWhite) 
			{
                app->compressImage(arrow2.dc, {arrow2.rect.getSize().x, arrow2.rect.getSize().y}, loadManager->loadImage ("arrow2WhiteVert.bmp"), {16, 16});
			}
		}



		if (horizontalMode) 
		{
			if (!isWhite) app->compressImage(dc, {rect.getSize ().x - arrow1.rect.getSize().x - arrow2.rect.getSize().x, rect.getSize ().y}, loadManager->loadImage ("SliderBackGroundHor.bmp"), {948, 13);
			if (isWhite) app->compressImage(dc, {rect.getSize ().x - arrow1.rect.getSize().x - arrow2.rect.getSize().x, rect.getSize ().y}, loadManager->loadImage ("SliderBackGroundWhiteHor.bmp"), {870, 16});
			//printBlt(dc);	 	 SliderBackGroundWhiteHot
		}
		else
		{
			if (!isWhite) app->compressImage(dc, {rect.getSize ().x, rect.getSize ().y - arrow1.rect.getSize().y - arrow2.rect.getSize().y}, loadManager->loadImage ("SliderBackGroundVert.bmp"), {13, 948});
			if (isWhite)  app->compressImage(dc, {rect.getSize ().x, rect.getSize ().y - arrow1.rect.getSize().y - arrow2.rect.getSize().y}, loadManager->loadImage ("SliderBackGroundWhite.bmp"), {16, 870});
		}

		if (horizontalMode)
		{
			sliderQuadrate.rect.pos.y       = 0;
			sliderQuadrate.rect.finishPos.y = rect.getSize ().y; 
			sliderQuadrate.rect.pos.x       = arrow1.rect.pos.x;
			sliderQuadrate.rect.finishPos.x = (rect.getSize ().x - arrow1.rect.getSize().x - arrow2.rect.getSize().x) * quadrateScale;
		}
		else
		{
			sliderQuadrate.rect.pos.x       = 1;
			sliderQuadrate.rect.finishPos.x = rect.getSize().x - 1;
			sliderQuadrate.rect.pos.y       = arrow1.rect.pos.y;
			sliderQuadrate.rect.finishPos.y = (rect.getSize ().y - arrow1.rect.getSize().y - arrow2.rect.getSize().y) * quadrateScale; 
		}

		if (horizontalMode)
		{
			axis = (rect.getSize().x - arrow2.rect.getSize ().x) - (arrow1.rect.getSize ().x) - rect.getSize().x * quadrateScale;
		}
		else
		{
			axis = (rect.getSize().y - arrow2.rect.getSize().y) - (arrow1.rect.getSize().y) - rect.getSize().y * quadrateScale;
		}




		if (horizontalMode) 
		{
			if (!isWhite)app->compressImage(sliderQuadrate.dc, { ceil (rect.getSize ().x * _quadrateScale), sliderQuadrate.rect.getSize().y}, loadManager->loadImage ("SliderRect.bmp"), {316, 12});
			if (isWhite)app->compressImage(sliderQuadrate.dc, { ceil (rect.getSize ().x * _quadrateScale), sliderQuadrate.rect.getSize().y}, loadManager->loadImage ("WhiteSliderRectHor.bmp"), {299, 1});
			sliderQuadrate.finalDC = txCreateCompatibleDC (ceil (rect.getSize ().x * _quadrateScale), sliderQuadrate.rect.getSize().y);
			sliderQuadrate.originalRect = {.pos = {0, 0}, .finishPos = {316, 12}};
			//printBlt (sliderQuadrate.dc);
		}
		else
		{

			if (!isWhite) app->compressImage(sliderQuadrate.dc, {sliderQuadrate.rect.getSize().x, ceil(rect.getSize().y *  _quadrateScale)}, loadManager->loadImage ("VerticalSliderRect.bmp"), {12, 316});
			if (isWhite) app->compressImage(sliderQuadrate.dc, {sliderQuadrate.rect.getSize().x, ceil (rect.getSize().y *  _quadrateScale)}, loadManager->loadImage ("WhiteSliderRect.bmp"), {14, 299});
			sliderQuadrate.finalDC = txCreateCompatibleDC (sliderQuadrate.rect.getSize().x, ceil (rect.getSize().y *  _quadrateScale));
			sliderQuadrate.originalRect = {.pos = {0, 0}, .finishPos = {12, 316}};
		}

		arrow1.finalDC = txCreateCompatibleDC (arrow1.rect.getSize().x, arrow1.rect.getSize().y);
		arrow2.finalDC = txCreateCompatibleDC (arrow2.rect.getSize().x, arrow2.rect.getSize().y);

        addWindow (&arrow1);
        addWindow (&arrow2);
        addWindow (&sliderQuadrate);
		 

	}

	void resize (Rect newRect);
	void deleteDC ();

	virtual void draw () override;
	virtual void onClick (Vector mp) override;
                                                                                                  
	virtual void deleteButton() override;

};