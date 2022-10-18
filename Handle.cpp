#pragma once
#include "Handle.h"


List* Handle::createMenuOption(const char* optionText, int* status, bool needToHideAfterClick/*= false*/)
{
    if (currentOptionsLength + 1 < maxOptionsLength)
    {      
        options[currentOptionsLength].optionStatus = status;
        char* relustOfCopy = strcpy(options[currentOptionsLength].name, optionText);

        app->selectFont(fontName, font, finalDC);
        Vector sizeOfLabel = app->getTextExtent(options[currentOptionsLength].name, finalDC);

        options[currentOptionsLength].size.x = sizeOfLabel.x + deltaBetweenFrameOfOption;
        options[currentOptionsLength].size.y = optionHeight;

        List* newList = new List(app, {}, {app->systemSettings->BUTTONWIDTH * 5, getSize().y}, 10, true, needToHideAfterClick);
        options[currentOptionsLength].list = newList;

        currentOptionsLength++;
        manager->addWindow(newList);

        return newList;
    }
    return NULL;
}

void Handle::setOptionsRect()
{
    double centrizedOptionPos = app->getCentrizedPos({0, optionHeight}, { 0, getSize().y }).y;

    for (int i = 0; i < currentOptionsLength; i++)
    {
        double lastRectFinishPos = 0;
        if (i > 0)
        {
            lastRectFinishPos = options[i - 1].rect.finishPos.x;
        }
        if (i == 0) options[i].rect.pos.x = startOfOptions;
        else        options[i].rect.pos.x = lastRectFinishPos + deltaBetweenOptions;
        
        options[i].rect.pos.y = centrizedOptionPos;


        options[i].rect.finishPos.x = options[i].rect.pos.x + options[i].size.x;
        options[i].rect.finishPos.y = options[i].rect.pos.y + options[i].size.y;

        options[i].list->MoveWindowTo({ options[i].rect.pos.x, options[i].rect.finishPos.y });
    }
}

void Handle::drawOptions()
{
      
    int numOfOption = coloredOptionNum;
    app->setColor(app->systemSettings->TextColor, finalDC);
    app->selectFont(fontName, font, finalDC);

    

    for (int i = 0; i < currentOptionsLength; i++)
    {
        if (numOfOption == i)
        {
            app->setColor(onMouseColor, finalDC);
            app->rectangle(options[i].rect, finalDC);
            app->setColor(app->systemSettings->TextColor, finalDC);
        }

        app->drawText(options[i].rect, options[i].name, finalDC);

        if (activeOptionNum < 0)
        {
            options[i].list->needToShow = false;
        }
    }

    if (activeOptionNum >= 0)
    {
        options[activeOptionNum].list->show();
    }
}

void Handle::controlOptionClicking()
{
    /*
    int num = onWhichOptionIsMP();
    if ((num) >= 0 && !isClickedLastTime())
    {
        if (num == activeOptionNum && !isClickedLastTime())
        {
            options[activeOptionNum].list->hide();
            activeOptionNum = -1;
            return;
        }
        activeOptionNum = num;
        options[activeOptionNum].list->show();
        return;
    }

    if (num >= 0) return;
    */
    /*
    if (activeOptionNum >= 0)
    {
        if (!options[activeOptionNum].list->needToShow)
        {
            activeOptionNum = -1;
            return;
        }

        int newActiveOptionNum = onWhichOptionIsMP();
        if (newActiveOptionNum != activeOptionNum && newActiveOptionNum >= 0)
        {
            options[activeOptionNum].list->hide();
            options[newActiveOptionNum].list->show();
            activeOptionNum = newActiveOptionNum;
            options[activeOptionNum].list->show();
        }

        if (getMBCondition() == 1)
        {
            if (!options[activeOptionNum].list->isActiveWindowBelow() && !(options[activeOptionNum].rect).inRect(getMousePos()))
            {
                options[activeOptionNum].list->hide();
                activeOptionNum = -1;
            }
        }
    }
    */

   // if (onWhichOptionMouseWasClicked >= 0)
    {
       // options[onWhichOptionMouseWasClicked].list->show();
    }
}

int Handle::onWhichOptionIsMP()
{
    return -1;
}

bool Handle::addWindowToStart(Window* window)
{
    Rect windowRect = {};
    windowRect.pos.x = rect.pos.x + oneItemInMenuSize.x * (getCurLen() - numberOfAddToBackElements);
    windowRect.pos.y = rect.pos.y;

    windowRect.finishPos.x = rect.pos.x + oneItemInMenuSize.x * (getCurLen() - numberOfAddToBackElements + 1);
    windowRect.finishPos.y = rect.pos.y + oneItemInMenuSize.y;

    window->resize(windowRect);

    return addWindow(window);
}

bool Handle::addWindowToBack(Window* window)
{
    Rect windowRect = {};
    windowRect.pos.x = rect.finishPos.x - oneItemInBackMenuSize.x * (getCurLen() + 1);
    windowRect.pos.y = rect.pos.y;

    windowRect.finishPos.x = rect.finishPos.x - oneItemInBackMenuSize.x * getCurLen();
    windowRect.finishPos.y = rect.pos.y + oneItemInBackMenuSize.y;

    window->resize(windowRect);

    addToBackElemetsPos[numberOfAddToBackElements] = getCurLen();
    numberOfAddToBackElements++;

    return addWindow(window);
}

void Handle::screenChanged()
{
    Rect newRect = { .pos = rect.pos, .finishPos = {app->systemSettings->SizeOfScreen.x, rect.pos.y + getSize().y} };
    resize(newRect);

    for (int i = 0; i < numberOfAddToBackElements; i++)
    {
        Rect windowRect = {};
        windowRect.pos.x = rect.finishPos.x - app->systemSettings->BUTTONWIDTH * (i + 1);
        windowRect.pos.y = rect.pos.y;

        windowRect.finishPos.x = rect.finishPos.x - app->systemSettings->BUTTONWIDTH * i;
        windowRect.finishPos.y = rect.finishPos.y;
        pointers[i]->resize(windowRect);
    }
}


void Handle::draw()
{

    app->setColor(color, finalDC);
    app->rectangle(rect - rect.pos, finalDC);

    app->transparentBlt(finalDC, logoStart, logoSize, logo);

    app->windowsLibApi->standartManagerDraw(this);

    controlOptionClicking();
    drawOptions();
    

    if (wasCommonHandlePlaceClicked)
    {
        Vector superAbsMP = app->getCursorPos();
        Vector delta = superAbsMP - lastTimeMousePos;
        if (wasInFullScreenLastTime != app->isFullScreen()) delta = {};
        
        if (app->systemSettings->debugMode >= 2) printf("delta: {%lf, %lf}\n", delta.x, delta.y);
        if (app->systemSettings->debugMode >= 2) printf("mp: {%lf, %lf}\n", superAbsMP.x, superAbsMP.y);

        if (delta != 0)
        {
            app->systemSettings->ScreenPos += delta;
            app->changeWindow({}, app->systemSettings->ScreenPos);
        }

        lastTimeMousePos = superAbsMP;
        if (wasCommonHandlePlaceClicked && getMBCondition() == 0)wasCommonHandlePlaceClicked = 0;
    }

    wasInFullScreenLastTime = app->isFullScreen();

    setMbLastTime();
}

int Handle::onMouseMove(Vector mp, Vector delta)
{
    
    int answer = getOptionNum(mp);
    if (activeOptionNum >= 0 && answer >= 0 && activeOptionNum != answer)
    {
        options[activeOptionNum].list->hide();
        activeOptionNum = answer;
        coloredOptionNum = answer;
        app->updateScreen(this);
    }
    
    if (activeOptionNum < 0 && coloredOptionNum != answer)
    {
        coloredOptionNum = answer;
        app->updateScreen(this);
    }
    

    app->windowsLibApi->standartManagerOnMouseMove(this, mp, delta);

    return 0;
}

int Handle::isOnOptionsDown()
{
    for (int i = 0; i < currentOptionsLength; i++)
    {
        if (options[i].list->isOnMeMbDown)
        {
            return i + 1;
        }
    }
    return 0;
}

int Handle::mbDown(Vector mp, int button)
{
    /*
    int was
    for (int i = 0; i < currentOptionsLength; i++)
    {
        if ()
    }
    */
    int isonOptDown = isOnOptionsDown();
    if (getOptionNum(mp) == -1 && !isonOptDown)
    {
        activeOptionNum = -1;
        coloredOptionNum = -1;
        app->updateScreen(this);
    }
    return 0;
}

void Handle::onClick(Vector mp)
{
    int resultOfClicking = app->windowsLibApi->standartManagerOnClick(this, mp);

    //controlOptionClicking();
    if (optionOnClick(mp) >= 0) return;

    

    if (logoRect.inRect(mp))
    {
        clickIcon();
        return;

    }

    if (resultOfClicking == -1 && !wasCommonHandlePlaceClicked)
    {
        if (app->isFullScreen())
        {
            app->changeWindow(app->systemSettings->lastTimeSizeOfScreen);
            app->setResized();
        }
        lastTimeMousePos = getAbsMousePos() + app->systemSettings->ScreenPos;
        wasCommonHandlePlaceClicked = true;
    }
    setMbLastTime();
}

int Handle::getOptionNum(Vector mp)
{
    int answer = -1;
    for (int i = 0; i < currentOptionsLength; i++)
    {
        if (options[i].rect.inRect(mp))
        {
            answer = i;

        }
    }

    return answer;
}

int Handle::optionOnClick(Vector mp)
{
    int answer = getOptionNum(mp);
    if (activeOptionNum != answer)
    {
        activeOptionNum = answer;
        coloredOptionNum = answer;
        app->updateScreen(this);
    }
    else
    {
        activeOptionNum = -1;
        app->updateScreen(this);
    }
    return activeOptionNum;
}

int Handle::onSize(Vector managerSize)
{
    Rect newRect = { .pos = rect.pos, .finishPos = {managerSize.x, rect.pos.y + getSize().y} };
    resize(newRect);

    setOptionsRect();

    for (int i = 0; i < numberOfAddToBackElements; i++)
    {
        Rect windowRect = {};
        windowRect.pos.x = rect.finishPos.x - app->systemSettings->BUTTONWIDTH * (i + 1);
        windowRect.pos.y = rect.pos.y;

        windowRect.finishPos.x = rect.finishPos.x - app->systemSettings->BUTTONWIDTH * i;
        windowRect.finishPos.y = rect.finishPos.y;
        pointers[i]->resize(windowRect);
    }
    return 0;
}


int Handle::onKeyboard(int key)
{
    int key1 = app->getKeyState(VK_CONTROL);
    int key2 = app->getKeyState('N');

    if (key1 && key2)
    {
        //if (app->canvasManager)app->canvasManager->openCreatingCanvasMenu();
    }
    return 0;
}



void Handle::clickIcon()
{
    char FAQ[4000] = {};

    FILE* faqFile = fopen("README3.md", "r");
    if (app->systemSettings->debugMode > 0)printf("faqFile[%p] errno:%d", faqFile, errno);
    if (!faqFile)
    {
        app->messageBox("Не удалось открыть FAQ", "Ошибка", MB_OK);
        return;
    }

    fread(FAQ, sizeof(char), 2000, faqFile);
    fclose(faqFile);

    app->messageBox(FAQ, "FAQ", MB_OK);
}

