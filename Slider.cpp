#pragma once
#include "Slider.h"

void clearDC(HDC dc, COLORREF color = TX_BLACK);

void Slider::deleteDC ()
{
	txDeleteDC (sliderQuadrate.dc);
	txDeleteDC (arrow1.dc);
	txDeleteDC (arrow2.dc);
	txDeleteDC (dc);
}

void Slider::resize (Rect newRect)
{
	//arrow1.resize ({.pos = newRect.getSize() * (arrow1.rect.pos / rect.getSize()), .finishPos = newRect.getSize() * (arrow1.rect.finishPos / rect.getSize())});
	//arrow2.resize ({.pos = newRect.getSize() * (arrow2.rect.pos / rect.getSize()), .finishPos = newRect.getSize() * (arrow2.rect.finishPos / rect.getSize())});
	//compressImage (dc, newRect.getSize(), rect.getSize());

	if (horizontalMode)
	{
		arrow1.rect.pos.x = 0;
		arrow1.rect.pos.y = 0;
		arrow1.rect.finishPos.x = (1) * (rect.getSize ().y);
		arrow1.rect.finishPos.y = rect.getSize ().y;

		arrow2.rect.pos.x = rect.getSize ().x - (1) * rect.getSize ().y;
		arrow2.rect.pos.y = 0;
		arrow2.rect.finishPos.x = rect.getSize ().x;
		arrow2.rect.finishPos.y = rect.getSize ().y;
	}
	else
	{
		arrow1.rect.pos.x = 0;
		arrow1.rect.pos.y = 0;
		arrow1.rect.finishPos.x = rect.getSize().x;
		arrow1.rect.finishPos.y = (1) * arrow1.rect.getSize().x;
		
		arrow2.rect.pos.x = 0;
		arrow2.rect.pos.y = rect.getSize().y - (1) * arrow1.rect.getSize().x;
		arrow2.rect.finishPos.x = rect.getSize().x;
		arrow2.rect.finishPos.y = rect.getSize().y;
	}

	rect = newRect;
	if (horizontalMode)
	{
		axis = (rect.getSize().x - arrow2.rect.getSize ().x) - (arrow1.rect.getSize ().x) - rect.getSize().x * quadrateScale;
	}
	else
	{
		axis = (rect.getSize().y - arrow2.rect.getSize ().y) - (arrow1.rect.getSize ().y) - rect.getSize().y * quadrateScale;
	}

	clearDC (arrow1.finalDC);
	clearDC (arrow2.finalDC);
	clearDC (finalDC);
}

void clearDC (HDC dc, COLORREF color /* = TX_BLACK*/)
{
	$s;
	txSetAllColors (color, dc);

	//txRectangle (0, 0, sysDCMAXSIZE, DCMAXSIZE, dc);
}




void Slider::deleteButton ()
{
	arrow1.deleteButton();
	arrow2.deleteButton();
	sliderQuadrate.deleteButton();
	if (dc) txDeleteDC (dc);
	if (finalDC) txDeleteDC (finalDC);
}

void Slider::draw ()
{
	if (maxNum - minNum != 0) kScale = axis / (maxNum - minNum);
	else kScale = 0;


	//int mx = mousePos.x;
	//int my = mousePos.y;
    //printf ("{%d}\n", mx);
	//mousePos =  {mx, my};

	//txBitBlt (finalDC, arrow2.rect.pos.x, arrow2.rect.pos.y, rect.getSize ().x, rect.getSize ().y, arrow2.finalDC);

	//upSideOfQuadrateSlider.draw ();
	//txBitBlt (finalDC, upSideOfQuadrateSlider.rect.pos.x, upSideOfQuadrateSlider.rect.pos.y, rect.getSize ().x, rect.getSize ().y, upSideOfQuadrateSlider.finalDC);

	//bottomSideOfQuadrateSlider.draw ();
	//txBitBlt (finalDC, bottomSideOfQuadrateSlider.rect.pos.x, bottomSideOfQuadrateSlider.rect.pos.y, rect.getSize ().x, rect.getSize ().y, bottomSideOfQuadrateSlider.finalDC);

	//sif (isClickedLastTime() == 0)sliderQuadrate.isClicked = false;

	
	//copyOnDC (sliderQuadrate.rect.pos.x, sliderQuadrate.rect.pos.y, sliderQuadrate.dc);
	//txBitBlt (finalDC, arrow2.rect.pos.x, arrow2.rect.pos.y, rect.getSize ().x, rect.getSize ().y, sliderQuadrate.dc);


    /*
	if (sliderQuadrate.isClicked)
	{
		if (horizontalMode && kScale != 0)  *num = tempNum + ( (mousePos.x - cursorStartPosition.x) / (kScale));
		if (!horizontalMode && kScale != 0) *num = tempNum + ( (mousePos.y - cursorStartPosition.y) / (kScale)); 

		if (*num > maxNum) *num = maxNum;
		if (*num < minNum) *num = minNum;
	}

	if (horizontalMode)
	{
		sliderQuadrate.rect.pos.x		= kScale * (*num - minNum) + arrow1.rect.finishPos.x;
		sliderQuadrate.rect.finishPos.x = kScale * (*num - minNum) + arrow1.rect.finishPos.x + quadrateScale * rect.getSize ().x;
	}
	else
	{
		sliderQuadrate.rect.pos.y		= kScale * (*num - minNum) + arrow1.rect.finishPos.y;
		sliderQuadrate.rect.finishPos.y = quadrateScale * rect.getSize ().y + sliderQuadrate.rect.pos.y;
	}

	txSetAllColors (TX_WHITE, finalDC);

	//if (horizontalMode)compressDraw (finalDC, {arrow1.rect.finishPos.x, arrow1.rect.pos.y }, {arrow2.rect.pos.x - arrow1.rect.finishPos.x, arrow2.rect.finishPos.y - arrow1.rect.pos.y}, dc, originalRect.getSize());
	if (horizontalMode)compressDraw (app, finalDC, {arrow1.rect.finishPos.x, arrow1.rect.pos.y }, {rect.getSize ().x, rect.getSize ().y}, dc, originalRect.getSize(), __LINE__);
	if (!horizontalMode)compressDraw (app, finalDC, {arrow1.rect.pos.x, arrow1.rect.finishPos.y }, {rect.getSize ().x, rect.getSize ().y}, dc, originalRect.getSize(), __LINE__);
	//if (horizontalMode) compressDraw (finalDC, {0, 0}, {rect.getSize ().x, rect.getSize ().y}, dc, originalRect.getSize());

	arrow1.draw ();
	compressDraw (app, finalDC, arrow1.rect.pos, arrow1.rect.getSize (), arrow1.finalDC, arrow1.originalRect.getSize (), __LINE__);
	//printBlt(arrow1.finalDC);
	//printBlt (arrow1.finalDC);
	//txBitBlt (finalDC, arrow1.rect.pos.x, arrow1.rect.pos.y, rect.getSize ().x, rect.getSize ().y, arrow1.finalDC);


	arrow2.draw ();
	compressDraw (app, finalDC, arrow2.rect.pos, arrow2.rect.getSize (), arrow2.finalDC, arrow2.originalRect.getSize (), __LINE__);
	//printBlt(finalDC);
	//txBitBlt(finalDC, arrow2.rect.pos.x, arrow2.rect.pos.y, arrow2.rect.getSize().x, arrow2.rect.getSize().y, arrow2.finalDC);

	//printBlt (sliderQuadrate.dc);
	sliderQuadrate.draw ();
	//txSetAllColors (TX_RED);
	//txRectangle (0, 0, 1000 ,1000);
	//txBitBlt (txDC(), 0, 0, 50, sliderQuadrate.rect.getSize ().y, sliderQuadrate.finalDC );
	
	//txSleep ();
	//stop;
	//printBlt (sliderQuadrate.finalDC)
	//txBitBlt (sliderQuadrate.finalDC, sliderQuadrate.rect.pos.x, sliderQuadrate.rect.pos.y, sliderQuadrate.rect.getSize ().x, sliderQuadrate.rect.getSize ().y);
	//printBlt(finalDC);
	txBitBlt (finalDC, sliderQuadrate.rect.pos.x, sliderQuadrate.rect.pos.y, sliderQuadrate.rect.getSize ().x, sliderQuadrate.rect.getSize ().y, sliderQuadrate.dc);
	//printBlt (finalDC);
    */
}

void Slider::onClick (Vector mp)
{
    /*
	int mx = mp.x;
	int my = mp.y;
    mousePos = mp;
	//Vector mousePos =  {mx, my};



	if (sliderQuadrate.rect.inRect (mx, my) && !isClickedLastTime())
	{
		cursorStartPosition = mp;
		tempNum = *num;
        sliderQuadrate.clicked = true;
	}

	if (arrow1.rect.inRect (mx, my) && *num > minNum && !isClickedLastTime())
	{
        arrow1.clicked = true;
		(*num)--;
	}
	if (arrow2.rect.inRect (mx, my) && *num < maxNum && !isClickedLastTime())
	{
        arrow2.clicked = true;
		(*num)++;
	}
    setMbLastTime();
    */
}


void printfDCS (const char *str)
{
    printf ("%s\n", str);
    for (int i = 0; i < _txCanvas_UserDCs->size (); i++)
    {
        printf ("%d: %p\n", i, (*_txCanvas_UserDCs)[i]);
    }
    _getch ();
}


