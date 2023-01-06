#pragma once
#include "WindowHandle.h"


int WindowHandle::onSize(Vector managerSize, Rect mewRect/* = {}*/)
{
    rect = { .pos = {0, 0}, .finishPos = {height, managerSize.x} };
    return 1;

}

void WindowHandle::print(M_HDC& _dc)
{
        
}