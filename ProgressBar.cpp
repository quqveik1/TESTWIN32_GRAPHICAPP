#pragma once
#include "ProgressBar.h"


void ProgressBar::setProgress(double* total, double* current)
{
    totalNum = total;
    currentNum = current;

};


void ProgressBar::draw()
{
    $s
        if (manager) app->setColor(manager->color, finalDC);
    app->rectangle(0, 0, rect.getSize().x, rect.getSize().y, finalDC);

    app->setColor(color, finalDC);
    if (totalNum && currentNum)
    {
        app->rectangle(0, 0, rect.getSize().x * (*currentNum / *totalNum), rect.getSize().y, finalDC);
    }
    //app->drawOnScreen(finalDC);
}