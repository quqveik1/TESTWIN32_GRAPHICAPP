#pragma once
#include "Q_Rect.h"
#include "EventMessage.h"
struct Option
{
    Vector size = {};
    Rect rect = {};
    const char* name = {};
    int* optionStatus = {};
    vector<struct Option*> subOptions;
    Window* reciever;
    EventMessage* eventMessage;

    virtual int addSubOption(Option* _option);
    virtual void addEventMessage(EventMessage* _eventMessage) { eventMessage = _eventMessage; };
    virtual void addReciever(Window* _reciever) { reciever = _reciever; };
    virtual void toLists(struct List*);
};