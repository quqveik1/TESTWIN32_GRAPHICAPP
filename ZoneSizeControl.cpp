#pragma once
#include "ZoneSizeControl.h"

void ZoneSizeControl::setFrameZones()
{

    upRect = { .pos = {frameThickness, 0}, .finishPos = {zone->getSize().x - frameThickness, frameThickness} };
    rightRect = { .pos = {zone->getSize().x - frameThickness, frameThickness}, .finishPos = {zone->getSize().x, zone->getSize().y - frameThickness} };
    bottomRect = { .pos = {frameThickness, zone->getSize().y - frameThickness}, .finishPos = {zone->getSize().x - frameThickness, zone->getSize().y} };
    leftRect = { .pos = {0, frameThickness}, .finishPos = {frameThickness, zone->getSize().y - frameThickness} };

    upLeft = { .pos = {}, .finishPos = {frameThickness, frameThickness} };
    upRight = { .pos = {zone->getSize().x - frameThickness, 0}, .finishPos = {zone->getSize().x, frameThickness} };
    bottomRight = { .pos = {zone->getSize().x - frameThickness, zone->getSize().y - frameThickness}, .finishPos = {zone->getSize().x, zone->getSize().y} };
    bottomLeft = { .pos = {0, zone->getSize().y - frameThickness}, .finishPos = {frameThickness, zone->getSize().y} };

}

int ZoneSizeControl::findZone()
{
    Vector mp = manager->getMousePos();
    if (activeZone) return activeZone;
    for (int i = 0; i < zonesNum; i++)
    {
        if (zones[i].rect->inRect(mp) || i == activeZone - 1)
        {
            return i + 1;
        }
    }
    return 0;
}

void ZoneSizeControl::setFrameCursor()
{
    if (activeZone > 0) manager->app->setCursor(zones[activeZone - 1].cursor);
}



void ZoneSizeControl::controlFrame()
{
    int mb = manager->getMBCondition();
    if (*needFrameToWork)
    {
        if (mb && wasZoneClicked || !mb && !wasZoneClicked)
        {
            setFrameZones();
            controlScreenResizing();
            activeZone = findZone();
            setFrameCursor();
        }
    }
    if (wasZoneClicked && mb != 1)
    {
        wasZoneClicked = false;
    }
}


void ZoneSizeControl::controlScreenResizing()
{
    if (!manager->getMBCondition() && activeZone) activeZone = 0;
    Vector superAbsMP = manager->app->getCursorPos();
    Vector delta = superAbsMP - mousePosLastTime;
    if (wasZoneClicked)
    {     
        bool needResizex = true;
        bool needResizey = true;
        Vector posBeforeRedacting = zone->pos;

        if (activeZone == 1)
        {
            zone->pos.y += delta.y;
        }
        if (activeZone == 2)
        {
            zone->finishPos.x += delta.x;
        }
        if (activeZone == 3)
        {
            zone->finishPos.y += delta.y;
        }
        if (activeZone == 4)
        {
            zone->pos.x += delta.x;
        }


        if (activeZone == 5)
        {
            zone->pos += delta;
        }
        if (activeZone == 6)
        {
            zone->pos.y += delta.y;
            zone->finishPos.x += delta.x;
        }
        if (activeZone == 7)
        {
            zone->finishPos += delta;
        }
        if (activeZone == 8)
        {
            zone->pos.x += delta.x;
            zone->finishPos.y += delta.y;
        }

        if (isSmaller(zone->getSize().x, minSize->x) || isEqual(zone->getSize().x, minSize->x))
        {
            zone->pos.x = posBeforeRedacting.x;
            zone->finishPos.x = zone->pos.x + minSize->x;
        }

        if (isSmaller(zone->getSize().y, minSize->y) || isEqual(zone->getSize().y, minSize->y))
        {
            zone->pos.y = posBeforeRedacting.y;
            zone->finishPos.y = zone->pos.y + minSize->y;
        }
    }

    mousePosLastTime = manager->app->getCursorPos();
}

void ZoneSizeControl::drawFrame()
{
    if (*needFrameToWork)
    {
        manager->app->drawCadre({ .pos = {0, -frameThickness}, .finishPos = zone->getSize() }, manager->finalDC, manager->color, lround(frameThickness));
    }
}

int ZoneSizeControl::clickFrame()
{
    if (*needFrameToWork) activeZone = findZone();
    if ((activeZone && manager->mbLastTime != manager->getMBCondition()))
    {
        wasZoneClicked = true;
        return 1;
    }
    if (wasZoneClicked)
    {
        return 1;
    }

    return 0;
}



