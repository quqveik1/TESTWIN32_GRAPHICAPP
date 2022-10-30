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
}