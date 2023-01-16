#pragma once
#include "ColorMenu.h"
#include "HSLPalette.cpp"




int ColorHistory::getByteSize()
{                      
    return sizeof(*this);
}


ColorMenu::ColorMenu(EngineAppApi* _app, Vector _pos, bool _needToShow /*= false*/) :
    sizeOfColorMenu({ 512, 410 }),
    Manager(_app, {}, 4, _needToShow, NULL, { .pos = {0, 0}, .finishPos = { 512, 25 } }),
    hslPalette(app, palettePos, &confirmedColor)
{
    needToControlHandleInDefaultFuncs = 1;
    assert(app);
    assert(app->systemSettings);
    addWindow(hslPalette);

    colorHistoryStartPos = { hslPalette.rect.pos.x, hslPalette.rect.finishPos.y + 25 };
    exampleColorStartPos = { colorHistoryStartPos.x,  colorHistoryStartPos.y + colorSectionSize.x + 15 };

    needTransparencyOutput = true;


    if (!app->makeDir("Settings"))strcpy(pathToSaveHistory, "Settings\\ColorMenu.save");

    loadHistory();
    colorExamplesNum = colorHistory.HistoryLength;
    exampleColorRects = new ColorSection[colorExamplesNum]{};
    setColorExamples();

    colorLastTime = app->systemSettings->DrawColor;


    if (colorHistory.currentPos - 1 < 0)
    {
        if (colorHistory.currHistoryLen == colorHistory.HistoryLength && colorHistory.colorHistory[colorHistory.HistoryLength - 1] != app->systemSettings->DrawColor)
        {
            confirmColor();
        }
        if (colorHistory.currHistoryLen == 0)
        {
            confirmColor();
        }
    }
    else if (colorHistory.colorHistory[colorHistory.currentPos - 1] != app->systemSettings->DrawColor)
    {
        confirmColor();
    }

    Rect newRect = { .pos = _pos, .finishPos = _pos + sizeOfColorMenu };
    resize(newRect);

    initPalette();

    handle.text = "Цвет";
    handle.font = app->systemSettings->MainFont + 5;

    setColorComponents();

    redChanger = new ColorComponentChanger(app, { .pos = {hslPalette.rect.finishPos.x + 25, handle.rect.finishPos.y + 25}, .finishPos = {hslPalette.rect.finishPos.x + 215, handle.rect.finishPos.y + 50} }, &redComponent, &confirmedColor, 1);
    addWindow(redChanger);

    greenChanger = new ColorComponentChanger(app, { .pos = {hslPalette.rect.finishPos.x + 25, redChanger->rect.finishPos.y + 5}, .finishPos = {hslPalette.rect.finishPos.x + 215, redChanger->rect.finishPos.y + 30} }, &greenComponent, &confirmedColor, 2);
    addWindow(greenChanger);

    blueChanger = new ColorComponentChanger(app, { .pos = {hslPalette.rect.finishPos.x + 25, greenChanger->rect.finishPos.y + 5}, .finishPos = {hslPalette.rect.finishPos.x + 215, greenChanger->rect.finishPos.y + 30} }, &blueComponent, &confirmedColor, 3);
    addWindow(blueChanger);

    currColorPos = app->getCentrizedPos({ 25, 25 }, { rect.getSize().x - hslPalette.rect.finishPos.x, 0 });
    currColorPos.x += hslPalette.rect.finishPos.x;
    currColorPos.y = blueChanger->rect.finishPos.y + 25;
}


void ColorMenu::loadHistory()
{
    FILE* saveFile = fopen(pathToSaveHistory, "r+b");
    if (!saveFile)
    {
        printf("История цветов не загрузилась(");
        return;
    }

    int byteSize = colorHistory.getByteSize();
    if (app->needToLoadOldFiles()) fread(&colorHistory, sizeof(char), byteSize, saveFile);
    fclose(saveFile);
}


int ColorMenu::onMouseMove(Vector mp, Vector delta)
{
    //app->systemSettings->DrawColor = RGB(redComponent, greenComponent, blueComponent);
    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);

    
    return 0;
}

int ColorMenu::mbDown(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbDown(this, mp, button);

    return 0;
}

int ColorMenu::mbUp(Vector mp, int button)
{
    app->windowsLibApi->standartManagerMbUp(this, mp, button);
    mbUpHandle();

    return 0;
}


int ColorMenu::onDestroy()
{
    saveMenu();
    return app->windowsLibApi->standartManagerOnDestroy(this);
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

    //redComponent = GetRValue(app->systemSettings->DrawColor);
    //greenComponent = GetGValue(app->systemSettings->DrawColor);
    //blueComponent = GetBValue(app->systemSettings->DrawColor);

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
        

        //app->bitBlt(finalDC, palettePos, {}, palette);

        
        app->setColor(app->systemSettings->DrawColor, finalDC);
        app->rectangle(currColorPos.x, currColorPos.y, currColorPos.x + 25, currColorPos.y + 25, finalDC);
        drawColorHistory();
        drawColorExamples();

    }
    app->systemSettings->DrawColor = RGB(redComponent, greenComponent, blueComponent);
    
    setMbLastTime();

    colorLastTime = app->systemSettings->DrawColor;
}



void ColorMenu::onClick(Vector mp)
{
    if (needToShow)
    {
        setActiveWindow(this);
        app->windowsLibApi->standartManagerOnClick(this, mp);

        controlHistoryClick();
        controlExampleClick();
    }
}

int ColorMenu::onKeyboard(int key)
{
    if (key == VK_ESCAPE)
    {
        hide(); 
        app->updateScreen(this);
    }
    app->windowsLibApi->standartManagerOnKeyboard(this, key);
    return 0;
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
    exampleColorRects[1].color = TX_LIGHTRED;
    exampleColorRects[2].color = TX_BLUE;
    exampleColorRects[3].color = TX_LIGHTBLUE;
    exampleColorRects[4].color = TX_GREEN;
    exampleColorRects[5].color = TX_LIGHTGREEN;
    exampleColorRects[6].color = TX_YELLOW;
    exampleColorRects[7].color = TX_CYAN;
    exampleColorRects[8].color = TX_LIGHTCYAN;
    exampleColorRects[9].color = TX_MAGENTA;
    exampleColorRects[10].color = TX_BROWN;
    exampleColorRects[11].color = TX_GRAY;
    exampleColorRects[12].color = TX_PINK;
    exampleColorRects[13].color = TX_WHITE;
    exampleColorRects[14].color = TX_BLACK;
    
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
    /*
    palette.setSize(paletteRect.getSize(), app);
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
    */
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
        printf("История цветов не сохранилась");
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