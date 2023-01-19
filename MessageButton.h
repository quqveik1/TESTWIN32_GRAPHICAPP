#pragma once
#include "TextView.h"

struct MessageButton : TextView
{
    const char* msgName = NULL;
    void* data = NULL;
    Window* reciever = NULL;

    MessageButton(AbstractAppData* _app) :
        TextView(_app)
    {
    }



    virtual void onClick(Vector mp) override;
    virtual Window* setReciever(Window* _reciver);
    virtual void setMessage(const char* _msgName, void* _data);


};