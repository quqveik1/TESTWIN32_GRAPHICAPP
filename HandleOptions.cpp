#pragma once

#include "HandleOptions.h"
#include "WindowHandle.cpp"
#include "OptionWindow.cpp"


void HandleOptions::setManagerHandle(struct ManagerHandle* _managerhandle)
{
    managerhandle = _managerhandle;
    manager = managerhandle;
}


int HandleOptions::addOption(Option* _option)
{
    List* newList = new List(app, { app->systemSettings->BUTTONWIDTH * 5, app->systemSettings->HANDLEHEIGHT });
    _option->addReciever(newList);

    OptionWindow* optionWindow = new OptionWindow(app, _option, { 0, height });
    optionsLayout.addWindow(optionWindow);
    optionsWindow.push_back(optionWindow);

    addWindow(newList);
    optionsList.push_back(newList);
    

    _option->toLists(newList);


    return mainOption.addSubOption(_option);
}



int HandleOptions::onSize(Vector managerSize, Rect newRect/* = {}*/)
{
    WindowHandle::onSize(managerSize, newRect);
    app->windowsLibApi->standartManagerOnSize(this, managerSize, newRect);


    for (size_t i = 0; i < optionsWindow.size(); i++)
    {
        optionsList[i]->MoveWindowTo({ optionsWindow[i]->rect.pos.x + optionsLayout.rect.pos.x, optionsWindow[i]->rect.finishPos.y + optionsLayout.rect.pos.y });
    }



    return 0;
}



void HandleOptions::draw()
{
    app->windowsLibApi->standartManagerDraw(this, {});

}