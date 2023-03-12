#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Double comparision.h"
#include <windef.h>



struct Vector 
{
    double x = 0;
    double y = 0;

    Vector& operator = (const Vector &a1);

    Vector& operator = (const double& num);
    explicit operator double ();

    explicit operator POINT() const;

    explicit operator SIZE() const;

    static Vector toVector(POINT point);
    static Vector toVector(SIZE point);

    static Vector getNullVector() { return Vector { 0,0 }; };
    void print (const char *str = NULL) const;
    const char* getStr(const char* str = NULL) const;
    int getIntX() const;    
    int getIntY() const;
    Vector& round();
    double delta() const;
};


Vector getNullVector()
{
    Vector _v = {};
    return _v;
}

#define NULL_VECTOR getNullVector() 

void equal (Vector &a, const Vector &b);
inline Vector operator +  (const Vector &a, const Vector &b);
inline Vector operator +  (const Vector &a, const double b);
inline Vector& operator += (Vector &a, const Vector &b);
inline Vector& operator -= (Vector& a, const Vector& b);
inline Vector operator -  (const Vector &a, const Vector &b);
inline Vector operator -  (const Vector &a, const double &num);
inline Vector operator - (const Vector& a);
inline void lining ();
inline Vector operator *  (const Vector &a, const double b);
inline Vector operator *  (const Vector &a, const Vector &b);
inline Vector& operator *= (Vector &a, const Vector &b);
inline Vector operator /  (const Vector &a, double m);
inline Vector operator /  (const Vector &a, const Vector &b);
inline Vector operator / (const double a, const Vector &b);
       Vector operator ^ (const Vector &vector, int degree);
       bool   operator > (const Vector &a, const Vector &b);
       bool   operator > (const Vector &a, const int &b);
       bool   operator < (const Vector &a, const int &b);
       bool   operator < (const Vector &a, const Vector &b);
       bool operator == (const Vector &a, const Vector &b);
       bool operator != (const Vector &a, const Vector &b); 
       bool operator == (const Vector &a, const double &b);
       bool operator != (const Vector &a, const double &b);

void Vector::print (const char *str /* = NULL*/) const
{
    printf (getStr(str));
}

const char* Vector::getStr(const char* str /*= NULL*/) const
{
    static char answer[MAX_PATH] = {};
    sprintf(answer, "%s: {%lf, %lf}", str, x, y);
    return answer;
}


int Vector::getIntX() const
{
    return lround(x);
}


int Vector::getIntY() const
{
    return lround(y);
}

Vector& Vector::round()
{
    x = getIntX();
    y = getIntY();
    return *this;
}

double Vector::delta() const
{
    return y - x;
}


Vector Vector::toVector(POINT point)  
{
    Vector res = {};
    res.x = point.x;                         
    res.y = point.y;
    return res;
} 

Vector Vector::toVector(SIZE point)
{
    Vector res = {};
    res.x = point.cx;
    res.y = point.cy;
    return res;   
}

bool operator == (const Vector &a, const Vector &b)
{
    if (isEqual (a.x, b.x) && isEqual(a.y, b.y)) return true;
    return false;
}  

bool operator != (const Vector &a, const Vector &b)
{
    return !(a == b);
}

bool operator != (const Vector& a, const double& b)
{
    if ( (!isEqual(a.x, b)) || (!isEqual(a.y, b)) ) return true;
    return false;
} 

bool operator == (const Vector& a, const double& b)
{
    if (isEqual(a.x, b) && isEqual(a.x, b)) return true;
    return false;
}

bool operator > (const Vector &a, const int &b)
{                                   
    if (isBigger(a.x, (double)b))
    {
        if (isBigger(a.y, (double)b))
        {
            return true;
        }
    }
    return false;
}


 bool operator < (const Vector &a, const int &b)
{                                   
    if (isSmaller(a.x, (double)b))
    {
        if (isBigger(a.y, (double)b))
        {
            return true;
        }
    }
    return false;
}

inline Vector operator * (const Vector &a, const double b)
{
    Vector result = {};
    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline Vector operator / (const double a, const Vector &b)
{
    Vector result = {};
    result.x = a / b.x;
    result.y = a / b.y;

    return result;
}

inline Vector operator + (const Vector &a, const Vector &b)
{
    Vector result = {};
    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline Vector operator +  (const Vector& a, const double b)
{
    Vector answer = {};
    answer.x = a.x + b;
    answer.y = a.y + b;
    
    return answer;
}

inline Vector operator - (const Vector &a, const Vector &b)
{
    Vector result = {};
    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline Vector operator -  (const Vector& a, const double& num)
{
    Vector result = {};
    result.x = a.x - num;
    result.y = a.y - num;

    return result;
}


inline Vector operator - (const Vector& a)
{
    Vector answer = {};
    answer.x = -a.x;
    answer.y = -a.y;
    return answer;
}




inline Vector &operator += (Vector &a, const Vector &b)
{
   a.x += b.x;
   a.y += b.y;
   
   return a;
}

inline Vector& operator -= (Vector& a, const Vector& b)
{
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

inline Vector operator * (const Vector &a, const Vector &b)
{
    Vector copyA  = a;
    return copyA *= b;
}

inline Vector &operator *= (Vector &a, const Vector &b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

inline Vector operator / (const Vector &a, double m)
{
    Vector answer = {};
    if (isEqual(m, 0))
    {
        printf("Zero dividing!\n");
        //(void)_getch();
    }
    else
    {
        answer.x = a.x / m;
        answer.y = a.y / m;
    }
    return answer;
} 

inline Vector operator / (const Vector &a, const Vector &b)
{
    Vector answer = {};
    if (isEqual(b.x, 0) || isEqual(b.y, 0))
    {
        printf("Zero dividing!\n");
        //(void)_getch();
    }
    answer.x = a.x / b.x;
    answer.y = a.y / b.y;
    return answer;
}

Vector operator ^ (const Vector &vector, int degree)    
{
    Vector result = {};
    for (int i = 1; i <= degree; i++)
    {
        //assert (0 <= i && i < BallMax);
        result.x = vector.x * vector.x;
        result.y = vector.y * vector.y;
    }

    return result;
};

inline void lining ()
{
    printf ("////////////////////////////////////\n");
}

bool operator > (const Vector &a, const Vector &b)
{
    if (isBigger (a.x, b.x))
    {
        if (isBigger(a.y, b.y))
        {
            return true;
        }

        else return false;
    }
    else return false;
}

bool operator < (const Vector &a, const Vector &b)
{
    if (isSmaller (a.x, b.x))
    {
        if (isSmaller(a.y, b.y))
        {
            return true;
        }

        else return false;
    }
    else return false;
}

void equal(Vector& a, const Vector& b)
{
    a.x = b.x;
    a.y = b.y;
}

Vector::operator double()
{
    return sqrt(x * x + y * y);
}

Vector& Vector::operator = (const double& num)
{
    x = num;
    y = num;

    return *this;
}

Vector& Vector::operator = (const Vector& a1)
{
    this->x = a1.x;
    this->y = a1.y;

    return *this;
};       

Vector::operator POINT() const
{
    POINT point = {};
    point.x = std::lround(x);
    point.y = std::lround(y);

    return point;

} 

Vector::operator SIZE() const
{
    SIZE point = {};
    point.cx = std::lround(x);
    point.cy = std::lround(y);

    return point;

}
