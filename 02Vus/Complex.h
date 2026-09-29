// Developed by Pavlo Vus on 22.02.2026
#pragma once
#include <iostream>

class TComplex;

class AComplex
{
    double _re, _im;
    static unsigned int _count;

public:
    AComplex(double re = 0, double im = 0);
    AComplex(const TComplex& a);
    AComplex(const AComplex& a);
    AComplex& operator=(const AComplex& a) &;
    ~AComplex();

    double re() const { return _re; }
    double im() const { return _im; }

    AComplex& operator+=(const AComplex& a) &;
    AComplex& operator-=(const AComplex& a) &;

    AComplex& operator*=(const AComplex& a) &;
    AComplex& operator/=(const AComplex& a) &;

    static unsigned int count() { return _count; }
};

std::ostream& operator<<(std::ostream& os, const AComplex& a);

AComplex operator+(AComplex a, const AComplex& b);
AComplex operator-(AComplex a, const AComplex& b);

TComplex operator*(const AComplex& a, const AComplex& b);
TComplex operator/(const AComplex& a, const AComplex& b);


class TComplex
{
    double _r, _phi;
    static unsigned int _count;
    void normalize();

public:
    TComplex(double r = 0, double phi = 0);
    TComplex(const AComplex& a);
    TComplex(const TComplex& a);
    TComplex& operator=(const TComplex& a) &;
    ~TComplex();

    double r()   const { return _r; }
    double phi() const { return _phi; }

    TComplex& operator*=(const TComplex& a) &;
    TComplex& operator/=(const TComplex& a) &;

    TComplex& operator+=(const TComplex& a) &;
    TComplex& operator-=(const TComplex& a) &;

    static unsigned int count() { return _count; }
};

std::ostream& operator<<(std::ostream& os, const TComplex& a);

TComplex operator*(TComplex a, const TComplex& b);
TComplex operator/(TComplex a, const TComplex& b);

AComplex operator+(const TComplex& a, const TComplex& b);
AComplex operator-(const TComplex& a, const TComplex& b);

AComplex operator+(const TComplex& a, const AComplex& b);
AComplex operator-(const TComplex& a, const AComplex& b);

AComplex operator+(const AComplex& a, const TComplex& b);
AComplex operator-(const AComplex& a, const TComplex& b);


TComplex operator*(const TComplex& a, const AComplex& b);
TComplex operator/(const TComplex& a, const AComplex& b);

TComplex operator*(const AComplex& a, const TComplex& b);
TComplex operator/(const AComplex& a, const TComplex& b);

AComplex operator+(double s, const AComplex& a);
AComplex operator-(double s, const AComplex& a);
TComplex operator*(double s, const AComplex& a);
TComplex operator/(double s, const AComplex& a);

AComplex operator+(double s, const TComplex& t);
AComplex operator-(double s, const TComplex& t);
TComplex operator*(double s, const TComplex& t);
TComplex operator/(double s, const TComplex& t);