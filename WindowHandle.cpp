#pragma once
#include "WindowHandle.h"
#include "WindowsLibApi.h"


int WindowHandle::onSize(Vector managerSize, Rect mewRect/* = {}*/)
{
    rect = { .pos = {0, 0}, .finishPos = {managerSize.x, height} };
    return 0;
}