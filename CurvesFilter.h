#pragma once
#include "DrawBibliothek.cpp"


struct Curves : Manager
{
    Rect graficrect;
    int numberOfPoints = 10;
    int pointsThickness = 3;
    int activePointNum = -1;
    Vector coordinatsSize = {255, 255};
    Vector *points = new Vector[numberOfPoints];
    bool isPointClickedLastTime = false;
    Vector lastTimeMousePos = {};
    Lay *activeLay = NULL;
    int permutation[256];
    Rect confirmButton;

    Curves (AbstractAppData* _app, Rect _rect, HDC _dc) :
        Manager (_app, _rect, 3, false, _dc, {.pos  = {0, 0}, .finishPos = {rect.getSize().x, 29}}),
        graficrect ({.pos = {55, 65}, .finishPos = {310, 320}}),
        confirmButton ({.pos = {360, 65}, .finishPos = {435, 80}})
    {
        Vector delta = coordinatsSize / 10;
        for (int i = 0; i < numberOfPoints; i++)
        {
            points[i].x = graficrect.pos.x + delta.x * i;
            points[i].y = graficrect.finishPos.y - delta.y * i;
        }
        for (int i = 0; i < 256; i++)
        {
            permutation[i] = i;
        }
    }

    void apply();
    void algorithm (RGBQUAD *pixel);
    void countPermutate ();

    virtual void draw() override;
    virtual void onClick (Vector mp) override;
};

void Curves::onClick (Vector mp)
{
    clickHandle();
    Vector mPos = mp;

    for (int i = 0; i < numberOfPoints; i++)
    {
        Rect point = {.pos = {points[i].x - pointsThickness, points[i].y - pointsThickness}, .finishPos = {points[i].x + pointsThickness, points[i].y + pointsThickness} };
        if (point.inRect(mPos.x, mPos.y))
        {
            activePointNum = i;    
        }
    }

    if (confirmButton.inRect(getRelativeMousePos().x, getRelativeMousePos().y)) apply();
}

void Curves::draw()
{
    standartDraw(this);
    txSetAllColors (TX_RED, finalDC);
    for (int i = 0; i < numberOfPoints; i++)
    {
        txEllipse (points[i].x - pointsThickness, points[i].y - pointsThickness, points[i].x + pointsThickness, points[i].y + pointsThickness, finalDC);
        if (i < numberOfPoints - 1) 
        {
            txLine (points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, finalDC);
        }
    }
    //activeLay = ActiveLay;
    
    
    if (activePointNum >= 0 )
    {
        //printf ("[num: %d|pos: {%lf, %lf}]  ", activePointNum, points[activePointNum].x, points[activePointNum].y);
        //if (drag (&points[activePointNum], &lastTimeMousePos, &isPointClickedLastTime, clicked))
        {
            activePointNum = -1;
            countPermutate ();
        }
        if (activePointNum > 0 && points[activePointNum].x < points[activePointNum - 1].x)  points[activePointNum].x = points[activePointNum - 1].x;
        if (activePointNum < numberOfPoints - 1 && points[activePointNum].x > points[activePointNum + 1].x)  points[activePointNum].x = points[activePointNum + 1].x;

    }
    if (txGetAsyncKeyState('W'))
    {
        endtillkey('W');
        apply();
    }
    controlHandle ();
}

void Curves::countPermutate ()
{
    Vector increaseK = graficrect.getSize() / coordinatsSize;
    int lastPointNum = -1;


    for (int i = 0; i < 256; i++)
    {
        int pixel = i * increaseK.x + graficrect.pos.x;
        for (int j = lastPointNum + 1; j < numberOfPoints; j++)
        {
            if (pixel >= points[j].x ) lastPointNum = j;
        }
        double localK = 0;
        if  (lastPointNum < numberOfPoints - 1) localK = (points[lastPointNum + 1].y - points[lastPointNum].y) / (points[lastPointNum + 1].x - points[lastPointNum].x);
        else localK = (graficrect.pos.y - points[lastPointNum].y) / (graficrect.finishPos.x - points[lastPointNum].x);
        if (i == 127) 
        {
            printf ("");
        }

        permutation[i] = ((pixel - points[lastPointNum].x) * localK + points[lastPointNum].y - graficrect.finishPos.y) / -increaseK.y; 
        //printf ("%d -> %d\n", i, permutation[i]);
    }
}

void Curves::algorithm (RGBQUAD *pixel)
{
    pixel->rgbRed = permutation[pixel->rgbRed];  
    pixel->rgbGreen = permutation[pixel->rgbGreen];  
    pixel->rgbBlue = permutation[pixel->rgbBlue];  
}

void Curves::apply()
{
    /*
    for (int x = 0; x < ActiveLay->laySize.x; x++)
	{
		for (int y = 0; y < activeLay->laySize.y; y++)
		{
			int pixelPos = (int) (activeLay->laySize.y - y) * ((int)(activeLay->laySize.x - 1)) + x;
			//RGBQUAD pixel = (*canvas)[pixelPos];

            //algorithm (&activeLay->layBuf[pixelPos]); 
            (activeLay->layBuf[pixelPos]).rgbRed =0;
            (activeLay->layBuf[pixelPos]).rgbGreen =0;
            (activeLay->layBuf[pixelPos]).rgbBlue =0;
		}
	}
    */
}