#pragma once

struct EventMessage
{
    virtual int onEvent(const char* tag, const char* sender) { return 0; };
    virtual int startEvent(const char* tag, const char* sender) { return onEvent(tag, sender); };
};