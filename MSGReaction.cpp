#pragma once
#include "MSGReaction.h"

int MSGReaction::getReaction()
{
    return reaction;
} 

int MSGReaction::setReaction(int r)
{
    return reaction = r;
}