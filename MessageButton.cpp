#pragma once
#include "TextView.cpp"
#include "MessageButton.h"

void MessageButton::onClick(Vector mp)
{
    if (reciever)
    {
        reciever->sendMessage(msgName, data);
    }
}

Window* MessageButton::setReciever(Window* _reciver)
{
    Window* oldReciever = reciever;
    reciever = _reciver;
    return oldReciever;
}

void MessageButton::setMessage(const char* _msgName, void* _data)
{
    msgName = _msgName;
    data = _data;
}

