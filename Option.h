#pragma once
#include "Q_Rect.h"
#include "EventMessage.h"
struct Option
{
    Vector size = {};
    Rect rect = {};
    char name[MAX_PATH] = {};
    int* optionStatus = {};
    vector<struct Option*> subOptions;
    EventMessage* eventMessage;

    virtual int addSubOption(Option* _option);
    virtual void addEventMessage(EventMessage* _eventMessage) { eventMessage = _eventMessage; };
};