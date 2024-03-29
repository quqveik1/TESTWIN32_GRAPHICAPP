#pragma once
#include "Q_Vector.h"

struct Rect
{
    Vector pos;
    Vector finishPos;
    Vector size;

    bool inRect (double x, double y) const;
    bool inRect (Vector vector) const;

    double left  () const { return this->pos.x; }
    double top   () const { return this->pos.y; }
    double right () const { return this->finishPos.x; }
    double bottom() const { return this->finishPos.y; }
    Vector getSize () const {return this->finishPos - this->pos; }
    void   countFinishPos() { this->finishPos = this->pos + this->size; }
    bool isValid () const;  
    Rect sort();
    void setHeight(double height);
    void setWidth(double height);
    void setSize(Vector _size);

    Rect& operator = (const Rect& a1);
    Rect& operator = (const RECT& a1);
    explicit operator RECT() const;
};

inline Rect operator + (const Rect &rect, const Vector &vector);
inline Rect operator - (const Rect &rect, const Vector &vector);
inline bool operator != (const Rect &rect1, const Rect &rect2);
inline bool operator != (const Rect &rect1, const double num);
inline bool operator == (const Rect &rect1, const double num);
inline bool operator == (const Rect &rect1, const Rect &rect2);

Rect& Rect::operator = (const Rect &a1)
{
    pos = a1.pos;
    finishPos = a1.finishPos;
    size = a1.size;

    return *this;
}

Rect& Rect::operator = (const RECT& a1)
{
    pos.x = a1.left;
    pos.y = a1.top;
    finishPos.x = a1.right;
    finishPos.y = a1.bottom;
    return *this;
}

Rect::operator RECT() const
{
    RECT result = {};
    result.left = std::lround(pos.x);
    result.top = std::lround(pos.y);
    result.right = std::lround(finishPos.x);
    result.bottom = std::lround(finishPos.y);

    return result;
}

bool Rect::inRect (double x, double y)  const
{
    if (isBigger(x, this->pos.x) && isBigger(y, this->pos.y))
    {
        if (isSmaller(x, this->finishPos.x) && isSmaller(y, this->finishPos.y))
        {
            return true;
        }
    }   
    return false;
}

bool Rect::inRect (Vector vector) const
{
    if (isBigger (vector.x, pos.x) ^ isBigger(vector.x, finishPos.x))
    {
        if (isBigger(vector.y, pos.y) ^ isBigger(vector.y, finishPos.y))
        {
            return true;
        }
    }

    /*
    if (vector.x > this->pos.x && vector.y > this->pos.y)
    {
        if (vector.x < this->finishPos.x && vector.y < this->finishPos.y)
        {
            return true;
        }
    } */  
    return false;
}

bool Rect::isValid() const
{
    if (getSize().x > 0 && getSize().y > 0) return true;
    return false;
}

Rect Rect::sort()
{
    if (isBigger(pos.x, finishPos.x))
    {
        double copy = finishPos.x;
        finishPos.x = pos.x;
        pos.x = copy;
    }   
    
    if (isBigger(pos.y, finishPos.y))
    {
        double copy = finishPos.y;
        finishPos.y = pos.y;
        pos.y = copy;
    }

    return *this;
}



void Rect::setHeight(double height)
{
    finishPos.y = pos.y + height;
} 

void Rect::setWidth(double width)
{
    finishPos.x = pos.x + width;
}

void Rect::setSize(Vector _size)
{
    setWidth(_size.x);
    setHeight(_size.y);
}



inline Rect operator + (const Rect& rect, const Vector& vector)
{
    Rect result = rect;
    result.pos += vector;
    result.finishPos += vector;

    return result;
}      

inline Rect operator - (const Rect& rect, const Vector& vector)
{
    Rect result = rect;
    result.pos -= vector;
    result.finishPos -= vector;

    return result;
}


inline bool operator != (const Rect& rect1, const Rect& rect2)
{
    return !(rect1 == rect2);
}     

inline bool operator != (const Rect& rect1, const double num)
{
    return !(rect1 == num);
}


inline bool operator == (const Rect& rect1, const double num)
{
    Vector _pos = { num, num };
    Vector _finishPos = { num, num };
    if (rect1.pos == _pos)
    {
        if (rect1.finishPos == _finishPos)
        {
            return true;
        }
    }
    return false;
}


inline bool operator == (const Rect& rect1, const Rect& rect2)
{
    if (rect1.pos == rect2.pos)
    {
        if (rect1.finishPos == rect2.finishPos)
        {
            return true;
        }
    }
    return false;
}