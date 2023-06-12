#pragma once
#include "HSLPalette.h"

void HSLPalette::initPalette()
{
    palette.setSize(rect.getSize(), app);
    for (int hue = 0; hue < 256; hue++)
    {
        for (int sat = 0; sat < 256; sat++)
        {
            //COLORREF pixelPos = sat * paletteSize.x + hue;
            COLORREF _hsl = RGB(hue, sat, lightness);
            COLORREF _rgb = app->HSL2RGB(_hsl);
            app->setPixel({ (double)hue, (double)sat }, _rgb, palette);
        }
    }
    app->bitBlt(finalDC, {}, {}, palette);
}

void HSLPalette::draw()
{
    if (colorLastTime != app->systemSettings->DrawColor)
    {
        COLORREF hslDrawColor = app->RGB2HSL(app->systemSettings->DrawColor);

        double hue = GetRValue(hslDrawColor);
        double sat = GetGValue(hslDrawColor);

        crossPos = { hue, sat };
        app->bitBlt(finalDC, {}, {}, palette);

        app->setColor(TX_WHITE, finalDC, (int)crossLineSize.x);
        app->line(crossPos.x, crossPos.y - (crossLineSize.y / 2), crossPos.x, crossPos.y + (crossLineSize.y / 2), finalDC);
        app->line(crossPos.x - (crossLineSize.y / 2), crossPos.y, crossPos.x + (crossLineSize.y / 2), crossPos.y, finalDC);
    }
}


int HSLPalette::mbDown(Vector mp, int button)
{
    if ((rect - rect.pos).inRect(mp))
    {
        isMovingCross = 1;
    }
    return 0;
}  

int HSLPalette::mbUp(Vector mp, int button)
{
    if (isMovingCross)
    {
        isMovingCross = 0;
        *confirmedColor = true;
        app->updateScreen(this);
    }
    return 0;
}

int HSLPalette::onMouseMove(Vector mp, Vector delta)
{
    if (isMovingCross)
    {
        if (delta != 0)
        {
            crossPos += delta;
            printf("Before Check: crossPos{%lf, %lf}, delta{%lf, %lf}\n", crossPos.x, crossPos.y, delta.x, delta.y);
            if (crossPos.x < crossLineSize.y)
            {
                crossPos.x = crossLineSize.y;
            } 

            if (crossPos.y < crossLineSize.y)
            {
                crossPos.y = crossLineSize.y;
            }

            if (crossPos.x > rect.getSize().x - crossLineSize.x)
            {
                crossPos.x = rect.getSize().x - crossLineSize.x;
            } 

            if (crossPos.y > rect.getSize().y - crossLineSize.x)
            {
                crossPos.y = rect.getSize().y - crossLineSize.x;
            }
            printf("After Check: crossPos{%lf, %lf}\n", crossPos.x, crossPos.y);
            app->systemSettings->DrawColor = app->HSL2RGB(RGB (crossPos.x, crossPos.y, lightness));
            app->updateScreen(this);
        }
    }
    return 0;
}