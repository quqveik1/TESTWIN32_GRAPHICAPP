#pragma once
#include "cmath"

double deltaOfComparision = 0.00001;

bool isEqual (const double& a, const double& b, const double delta = deltaOfComparision);
bool isBigger(const double& a, const double& b, const double delta = deltaOfComparision);
bool isSmaller(const double& a, const double& b, const double delta = deltaOfComparision);



bool isEqual(const double& a, const double& b, const double delta/* = deltaOfComparision*/)
{
    if (fabs(a - b) < delta) return true;
    else                     return false;
}

bool isBigger(const double& a, const double& b, const double delta/* = deltaOfComparision*/)
{
    if (a - b > delta) return true;
    else               return false;

}

bool isSmaller(const double& a, const double& b, const double delta/* = deltaOfComparision*/)
{
    if (b - a > delta) return true;
    else               return false;

}