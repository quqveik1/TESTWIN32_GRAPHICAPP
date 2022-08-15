#include "TouchButton.h"

void TouchButton::onClick(Vector mp)
{
    if (!isClickedLastTime()) *flag = true;
    setMbLastTime();
}