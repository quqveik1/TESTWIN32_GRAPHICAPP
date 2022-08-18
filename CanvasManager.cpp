#pragma once
#include "CanvasManager.h"
#include "Canvas.cpp"
#include "InputButton2.cpp"
#include "ImportTool.cpp"

CanvasManager::CanvasManager(AbstractAppData* _app, Vector _pos) :
    Manager(_app, { .pos = _pos, .finishPos = _app->systemSettings->FullSizeOfScreen }, 10, true, NULL, {}, TX_BLACK),
    oneTabSize({ app->systemSettings->BUTTONWIDTH * 5, app->systemSettings->HANDLEHEIGHT }),
    scaleButtonSize({75, 25}),
    plusMinusButtonSize({25, 25}),
    plusButtonDC(app->loadManager->loadImage("plusScaleButton.bmp")),
    minusButtonDC(app->loadManager->loadImage("minusScaleButton.bmp")),
    scaleButton(new InputButton2 (_app, { .pos = {}, .finishPos = scaleButtonSize }, &intScale, &minScale, &maxScale, 1, color)),
    importTool(new ImportTool(_app))
{
    gassert(loadManager);

    color = TX_BLACK;

    app->toolManager->addTool(importTool, true);

    tabCross = app->loadManager->loadImage("tabCross.bmp");

    addWindow(scaleButton);
}
Canvas* CanvasManager::getActiveCanvas()
{
    if (activeCanvasNum < 0) return NULL;
    return canvases[activeCanvasNum];
}

int CanvasManager::getActiveCanvasNum()
{
    return activeCanvasNum;
}

void CanvasManager::drawTabs()
{
    app->setColor(app->systemSettings->MenuColor, finalDC);
    app->rectangle({}, { getSize().x, oneTabSize.y }, finalDC);

    app->setColor(TX_BLACK, finalDC, 1);
    app->line({0, 1}, { getSize().x, 1 }, finalDC);
    app->line({0, oneTabSize.y}, { getSize().x, oneTabSize.y }, finalDC);
    if (!getActiveCanvas())
    {
        app->setColor(app->systemSettings->TextColor, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, font, finalDC);
        app->drawText({ .pos = {}, .finishPos = {getSize().x, oneTabSize.y} }, "FAQ доступен при клике на логотип слева наверху", finalDC, DT_VCENTER);
    }

    for (int i = 0; i < currentCanvasesLength; i++)
    {
        app->setColor(app->systemSettings->TextColor, finalDC);
        app->selectFont(app->systemSettings->FONTNAME, font, finalDC);
        app->drawText({ .pos = tabs[i].pos, .finishPos = {tabs[i].finishPos.x - tabCrossSize.x, tabs[i].finishPos.y} }, canvases[i]->getName(), finalDC);

        app->bitBlt(finalDC, { tabs[i].finishPos.x - tabCrossSize.x, tabs[i].pos.y }, {}, tabCross);

        COLORREF cadreColor = TX_BLACK;
        if (i == activeCanvasNum) cadreColor = TX_WHITE;
        app->drawCadre(tabs[i], finalDC, cadreColor, 2);
    }
}

void CanvasManager::setTabsRect()
{
    Rect userRect = app->getUserRect();
    userRect = userRect - rect.pos;
    for (int i = 0; i < currentCanvasesLength; i++)
    {
        tabs[i] = { .pos = {userRect.pos.x + oneTabSize.x * i, 0}, .finishPos = {userRect.pos.x + oneTabSize.x * (i + 1), oneTabSize.y } };
    }
}

void CanvasManager::controlScaleButtons()
{
    Rect userRect = app->getUserRect();
    userRect = userRect - rect.pos;

    Vector scaleButtonPos = { userRect.pos.x, userRect.finishPos.y - scaleButton->getSize().y };

    intScale = std::lround (getActiveCanvas()->getScale() * 100);
    scaleButton->MoveWindowTo(scaleButtonPos);
    scaleButton->draw();
    

    minusButtonRect = { .pos = {scaleButtonPos.x + scaleButton->getSize().x,  userRect.finishPos.y - plusMinusButtonSize.y}, .finishPos = {scaleButtonPos.x + scaleButton->getSize().x + plusMinusButtonSize.x, userRect.finishPos.y} };
    plusButtonRect = { .pos = {minusButtonRect.finishPos.x,    userRect.finishPos.y - plusMinusButtonSize.y}, .finishPos = {minusButtonRect.finishPos.x + plusMinusButtonSize.x,    userRect.finishPos.y} };
}


void CanvasManager::drawScaleButtons()
{
    app->bitBlt(finalDC, scaleButton->rect.pos, scaleButton->getSize(), scaleButton->finalDC);

    app->bitBlt(finalDC, plusButtonRect.pos, {}, plusButtonDC);
    app->bitBlt(finalDC, minusButtonRect.pos, {}, minusButtonDC);
}





void CanvasManager::draw()
{
    rect.finishPos = app->systemSettings->SizeOfScreen;

    app->setColor(color, finalDC);
    app->rectangle(0, 0, getSize().x, getSize().y, finalDC);

    if (getActiveCanvas())
    {

        controlScaleButtons();
        controlActiveCanvas();

        drawScaleButtons();
    }

    drawTabs();

    setMbLastTime();
}

void CanvasManager::controlActiveCanvas()
{
    if (getActiveCanvas())
    {
        getActiveCanvas()->getScale() = (double)intScale / 100.0;

        //controlStretching();
        //controlPosition();

        getActiveCanvas()->print(finalDC, app->MAINWINDOW);
    }
}

void CanvasManager::controlPosition()
{
    if (getActiveCanvas())
    {
        if (app->getKeyState(VK_RIGHT) && app->getKeyState(VK_CONTROL))
        {
            getActiveCanvas()->deltaPos.x -= 10;
        }
        if (app->getKeyState(VK_LEFT) && app->getKeyState(VK_CONTROL))
        {
            getActiveCanvas()->deltaPos.x += 10;
        }
        if (app->getKeyState(VK_UP) && app->getKeyState(VK_CONTROL))
        {
            getActiveCanvas()->deltaPos.y += 10;
        }
        if (app->getKeyState(VK_DOWN) && app->getKeyState(VK_CONTROL))
        {
            getActiveCanvas()->deltaPos.y -= 10;
        }
    }

    Vector сanvasPos = app->getCentrizedPos(getActiveCanvas()->getSize(), getSize());
    if (app->systemSettings->debugMode >= 3)printf("canvasPos: {%lf, %lf}\n", сanvasPos.x, сanvasPos.y);
    if (app->systemSettings->debugMode >= 3)printf("getActiveCanvas()->getSize(): {%lf, %lf}\n", getActiveCanvas()->getSize().x, getActiveCanvas()->getSize().y);
    if (app->systemSettings->debugMode >= 3)printf("getSize(): {%lf, %lf}\n", getSize().x, getSize().y);
    if (app->systemSettings->debugMode >= 3)printf("Canvas deltaPos: {%lf, %lf}\n", getActiveCanvas()->deltaPos.x, getActiveCanvas()->deltaPos.y);
    сanvasPos += getActiveCanvas()->deltaPos;
    getActiveCanvas()->MoveWindowTo(сanvasPos);
}

void CanvasManager::controlStretching()
{
    if (clock() - lastTimeButtonClicked > deltaBetween2Clicks && getActiveCanvas())
    {
        if (app->getKeyState(VK_CONTROL) && app->getKeyState(VK_OEM_PLUS))
        {
            getActiveCanvas()->stretchCanvas(getActiveCanvas()->deltaScale);
            lastTimeButtonClicked = clock();
        }

        if (app->getKeyState(VK_CONTROL) && app->getKeyState(VK_OEM_MINUS))
        {
            getActiveCanvas()->stretchCanvas(- (getActiveCanvas()->deltaScale));
            lastTimeButtonClicked = clock();
        }

    }
}

int CanvasManager::setDrawingMode(int num)
{
    Canvas* canvas = getActiveCanvas();

    if (num > 0)
    {
        bool needToChangeDrawingMode = false;
        if (canvas)
        {
            if (!canvas->getEditingMode())
            {
                needToChangeDrawingMode = true;
            }
        }
        else
        {
            needToChangeDrawingMode = true;
        }

    }
    return 1;
}

Vector CanvasManager::getCentrizedPos(Vector localSize, Vector globalSize)
{
    return (globalSize - localSize) * 0.5;
}

bool CanvasManager::addCanvas(const char* name, Vector dcSize)
{
    canvases[currentCanvasesLength] = new Canvas(app, { .pos = getCentrizedPos(dcSize, getSize()), .finishPos = getCentrizedPos(dcSize, getSize()) + dcSize }, name);
    activeCanvasNum = currentCanvasesLength;
    currentCanvasesLength++;
    setTabsRect();
    return addWindow(canvases[currentCanvasesLength - 1]);
}

int CanvasManager::onKeyboard(int key)
{
    controlStretching();
    controlPosition();
    return 1;
}

void CanvasManager::onClick(Vector mp)
{
    if (tabsOnClick() >= 0) return;

    if (getActiveCanvas())
    {
        mp = getMousePos();
        if (scaleButton->rect.inRect(mp))
        {
            scaleButton->onClick(mp);
            return;
        }

        if (plusButtonRect.inRect(mp))
        {
            if (!isClickedLastTime()) getActiveCanvas()->stretchCanvas(getActiveCanvas()->deltaScale);
            return;
        }

        if (minusButtonRect.inRect(mp))
        {
            if (!isClickedLastTime()) getActiveCanvas()->stretchCanvas( -(getActiveCanvas()->deltaScale) );
            return;
        }

        if (getActiveCanvas()->rect.inRect(mp))getActiveCanvas()->onClick(mp);
    }

    setMbLastTime();
}

int CanvasManager::tabsOnClick()
{
    Vector mp = getMousePos();
    for (int i = 0; i < currentCanvasesLength; i++)
    {
        if (tabs[i].inRect(mp))
        {
            activeCanvasNum = i;
            Rect crossRect = { .pos = {tabs[i].finishPos.x - tabCrossSize.x, tabs[i].pos.y}, .finishPos = {tabs[i].finishPos.x, tabs[i].finishPos.y} };
            if (crossRect.inRect(mp) && !isClickedLastTime())
            {
                deleteCanvas(i);
                break;
            }
            return activeCanvasNum;
        }
    }
    return -1;
}

void CanvasManager::deleteCanvas(int num)
{
    if (canvases[num])
    {
        delete canvases[num];
    }

    int oneItemSize = sizeof(Canvas*);
    app->shiftArrBack((char*)canvases, oneItemSize, num + 1, currentCanvasesLength);
    currentCanvasesLength--;
    int oldCanvasNum = getActiveCanvasNum();
    if (setActiveCanvas(oldCanvasNum - 1))
    {
        setActiveCanvas(oldCanvasNum + 1);
    }
}

int CanvasManager::setActiveCanvas(int num)
{
    if (num >= 0 && num < currentCanvasesLength)
    {
        activeCanvasNum = num;
        return !"Sucsess";
    }
    activeCanvasNum = -1;
    return (int)"Error";
}

void CanvasManager::deleteButton()
{

    for (int i = 0; i < length; i++)
    {
        if (pointers[i]) pointers[i]->deleteButton();
    }
}

void CanvasManager::screenChanged()
{
    rect.finishPos = app->systemSettings->SizeOfScreen;
    Vector centrizedPos = {};
    Vector tempSize = {};
    for (int i = 0; i < currentCanvasesLength; i++)
    {
        if (canvases[i])
        {
            tempSize = canvases[i]->rect.getSize();
            centrizedPos = app->getCentrizedPos(tempSize, getSize());
            canvases[i]->MoveWindowTo(centrizedPos);
        }
    }

    setTabsRect();
}

int CanvasManager::onSize(Vector managerSize)
{
    rect.finishPos = managerSize;
    Vector centrizedPos = {};
    Vector tempSize = {};
    for (int i = 0; i < currentCanvasesLength; i++)
    {
        if (canvases[i])
        {
            tempSize = canvases[i]->rect.getSize();
            centrizedPos = app->getCentrizedPos(tempSize, getSize());
            canvases[i]->MoveWindowTo(centrizedPos);
        }
    }

    setTabsRect();
    return 0;
}
