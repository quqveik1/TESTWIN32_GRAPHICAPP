#pragma once
#include "ColorMenu.h"


int ColorHistory::getByteSize()
{                      
    return sizeof(*this);
}


void ColorMenu::loadHistory()
{
    FILE* saveFile = fopen(pathToSaveHistory, "r+b");
    if (!saveFile)
    {
        printf("������� ������ �� �����������(");
        return;
    }

    int byteSize = colorHistory.getByteSize();
    if (app->needToLoadOldFiles()) fread(&colorHistory, sizeof(char), byteSize, saveFile);
    fclose(saveFile);
}


int ColorMenu::onMouseMove(Vector mp, Vector delta)
{
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);
    moveHandle(delta);
    return 0;
}

int ColorMenu::mbDown(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbDown(this, mp, button);
    clickHandle();

    return 0;
}

int ColorMenu::mbUp(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbUp(this, mp, button);
    mbUpHandle();

    return 0;
}

void ColorMenu::show()
{
    setColorComponents();
    app->windowsLibApi->standartManagerShow(this);
}

void ColorMenu::draw()
{
    assert(app);
    assert(app->systemSettings);

    app->setColor(color, finalDC);
    app->rectangle(rect - rect.pos, finalDC);
    app->windowsLibApi->standartManagerDraw(this);
    handle.print(finalDC);

    if (app->systemSettings->debugMode >= 3)printf("colorHistory.currentPos: %d\n", colorHistory.currentPos);
    
    if (confirmedColor)
    {
        confirmColor();
    }
    if (needToShow)
    {
        app->setColor(splitLinesColor, finalDC);
        app->line(0, handle.rect.finishPos.y, getSize().x, handle.rect.finishPos.y, finalDC);
        //app->setColor(app->systemSettings->DrawColor, finalDC);
        //app->rectangle(220, 85, 245, 110, finalDC);

        drawColorHistory();
        drawColorExamples();

    }
    app->systemSettings->DrawColor = RGB(redComponent, greenComponent, blueComponent);
    
    setMbLastTime();

    colorLastTime = app->systemSettings->DrawColor;
}



void ColorMenu::onClick(Vector mp)
{
    setActiveWindow(this);
    app->windowsLibApi->standartManagerOnClick(this, mp);

    controlHistoryClick();
    controlExampleClick();
}

void ColorMenu::controlHistoryClick()
{
    int clickedI = -1;
    setColorHistoryRects();
    for (int i = 0; i < colorHistory.currHistoryLen; i++)
    {
        if (colorHistory.colorRect[i].inRect(getMousePos()) && !isClickedLastTime()) clickedI = i;
    }

    if (clickedI < 0) return;

    COLORREF copyColor = colorHistory.colorHistory[clickedI];

    moveHistory(clickedI);
    colorHistory.colorHistory[colorHistory.currentPos - 1] = copyColor;
    app->systemSettings->DrawColor = copyColor;
    setColorComponents();
    app->updateScreen(this);
}

void ColorMenu::setColorComponents()
{
    redComponent = GetRValue (app->systemSettings->DrawColor);
    greenComponent = GetGValue (app->systemSettings->DrawColor);
    blueComponent = GetBValue(app->systemSettings->DrawColor);
}


void ColorMenu::drawColorHistory()
{
    setColorHistoryRects();
    for (int i = 0; i < colorHistory.currHistoryLen; i++)
    {
        app->setColor(colorHistory.colorHistory[i], finalDC);
        app->rectangle(colorHistory.colorRect[i], finalDC);

        app->drawCadre(colorHistory.colorRect[i], finalDC, frameColor, 2);
    }

    setMbLastTime();
}


void ColorMenu::setColorExamples()
{
    
    for (int i = 0; i < colorExamplesNum; i++)
    {

        exampleColorRects[i].section = { .pos = { exampleColorStartPos.x + 30 * i, exampleColorStartPos.y}, .finishPos = { exampleColorStartPos.x + colorSectionSize.x + 30 * (i), exampleColorStartPos.y + colorSectionSize.y} };
        
    }

    exampleColorRects[0].color = TX_RED;
    exampleColorRects[1].color = TX_BLUE;
    exampleColorRects[2].color = TX_GREEN;
    exampleColorRects[3].color = TX_CYAN;
    exampleColorRects[4].color = TX_MAGENTA;
    exampleColorRects[5].color = TX_BROWN;
    exampleColorRects[6].color = TX_GRAY;
    exampleColorRects[7].color = TX_PINK;
    exampleColorRects[8].color = TX_WHITE;
    exampleColorRects[9].color = TX_BLACK;
    exampleColorRects[10].color = TX_YELLOW;
}

void ColorMenu::controlExampleClick()
{
    Vector mp = getMousePos();
    for (int i = 0; i < colorExamplesNum; i++)
    {
        if (exampleColorRects[i].section.inRect(mp))
        {
            app->setDrawColor(exampleColorRects[i].color);
            setColorComponents();
            if (colorLastTime != exampleColorRects[i].color) confirmColor();
            app->updateScreen(this);
        }
    }
}

void ColorMenu::initPalette()
{
    palette.setSize(paletteSize, app);
    for(int hue = 0; hue)
}


void ColorMenu::drawColorExamples()
{
    for (int i = 0; i < colorExamplesNum; i++)
    {
        drawOneColorSection(exampleColorRects[i].section, exampleColorRects[i].color);
    }
}

void ColorMenu::drawOneColorSection(Rect sectionRect, COLORREF sectionColor)
{
    app->setColor(sectionColor, finalDC);
    app->rectangle(sectionRect, finalDC);
    app->drawCadre(sectionRect, finalDC, frameColor, 2);
}



void ColorMenu::moveHistory(int clickedNumOfColorRect)
{
    if (clickedNumOfColorRect == colorHistory.currentPos - 1 || (colorHistory.currentPos == 0 && clickedNumOfColorRect == colorHistory.HistoryLength - 1))  return;

    int startNumSecondCircle = clickedNumOfColorRect;

    if (clickedNumOfColorRect > colorHistory.currentPos - 1)
    {
        for (int i = clickedNumOfColorRect + 1; i < colorHistory.currHistoryLen; i++)
        {
            colorHistory.colorHistory[i - 1] = colorHistory.colorHistory[i];
        }
        colorHistory.colorHistory[colorHistory.currHistoryLen - 1] = colorHistory.colorHistory[0];
        startNumSecondCircle = 0;
    }

    for (int i = startNumSecondCircle + 1; i <= colorHistory.currentPos - 1; i++)
    {
        if (i > 0)colorHistory.colorHistory[i - 1] = colorHistory.colorHistory[i];
    }
}




void ColorMenu::confirmColor()
{
    bool needToSaveColor = false;
    if (colorHistory.currentPos > 0)
    {
        if (colorHistory.colorHistory[colorHistory.currentPos - 1] != app->systemSettings->DrawColor)
        {
            needToSaveColor = true;
        }
    }
    else 
    {
        if (colorHistory.currHistoryLen == colorHistory.HistoryLength)
        {
            if (colorHistory.colorHistory[colorHistory.currHistoryLen - 1] != app->systemSettings->DrawColor)
            {
                needToSaveColor = true;
            }
        }


        if (colorHistory.currHistoryLen == 0)
        {
            needToSaveColor = true;
        }
    }

    if (needToSaveColor)
    {

        if (colorHistory.currHistoryLen < colorHistory.HistoryLength) colorHistory.currHistoryLen++;
        colorHistory.colorHistory[colorHistory.currentPos] = app->systemSettings->DrawColor;

        if (colorHistory.currentPos < colorHistory.HistoryLength - 1) colorHistory.currentPos++;
        else                colorHistory.currentPos = 0;
    }

    confirmedColor = false;
}

void ColorMenu::saveMenu()
{
    FILE* saveFile = fopen(pathToSaveHistory, "w+b");
    if (!saveFile)
    {
        printf("������� ������ �� �����������");
        return;
    }

    int byteSize = colorHistory.getByteSize();
    fwrite(&colorHistory, sizeof(char), byteSize, saveFile);
    fclose(saveFile);
}


void ColorMenu::setColorHistoryRects()
{
    for (int i = colorHistory.currentPos - 1; i >= 0; i--)
    {
        int orderI = colorHistory.currentPos - 1 - i;
        Rect colorsRect = { .pos = { colorHistoryStartPos.x + (colorSectionSize.x + 5) * orderI, colorHistoryStartPos.y}, .finishPos = { colorHistoryStartPos.x + colorSectionSize.x + (colorSectionSize.x + 5) * (orderI), colorHistoryStartPos.y + colorSectionSize.y} };
        colorHistory.colorRect[i] = colorsRect;
    }

    for (int i = colorHistory.currHistoryLen - 1; i >= colorHistory.currentPos; i--)
    {
        int orderI = colorHistory.currentPos + (colorHistory.currHistoryLen - 1 - i);
        Rect colorsRect = { .pos = { colorHistoryStartPos.x + (colorSectionSize.x + 5) * orderI, colorHistoryStartPos.y}, .finishPos = { colorHistoryStartPos.x + colorSectionSize.x + (colorSectionSize.x + 5) * (orderI), colorHistoryStartPos.y + colorSectionSize.y} };
        colorHistory.colorRect[i] = colorsRect;
    }
}