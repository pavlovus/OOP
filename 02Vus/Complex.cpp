// Developed by Pavlo Vus on 22.02.2026
#include "Complex.h"

unsigned int AComplex::_count = 0;
unsigned int TComplex::_count = 0;

AComplex::AComplex(const double re, const double im) : _re(re), _im(im)
{
    _count++;
#ifndef NDEBUG
    std::cout << "Created AComplex\n";
#endif
}

AComplex::AComplex(const TComplex& a)
{
    _re = a.r() * std::cos(a.phi());
    _im = a.r() * std::sin(a.phi());
    _count++;
#ifndef NDEBUG
    std::cout << "Converted: TComplex -> AComplex\n";
#endif
}

AComplex::AComplex(const AComplex& a) : _re(a._re), _im(a._im) { _count++; }

AComplex& AComplex::operator=(const AComplex& a) &
{
    if (this != &a) { _re = a._re; _im = a._im; }
    return *this;
}

AComplex::~AComplex() { _count--; }

AComplex& AComplex::operator+=(const AComplex& a) &
{
    _re += a._re;
    _im += a._im;
    return *this;
}

AComplex& AComplex::operator-=(const AComplex& a) &
{
    _re -= a._re;
    _im -= a._im;
    return *this;
}

AComplex& AComplex::operator*=(const AComplex& a) &
{
    TComplex t(*this);
    t *= TComplex(a);
    *this = AComplex(t);
    return *this;
}

AComplex& AComplex::operator/=(const AComplex& a) &
{
    TComplex t(*this);
    t /= TComplex(a);
    *this = AComplex(t);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const AComplex& a)
{
    return os << a.re() << (a.im() >= 0 ? " + " : " ") << a.im() << "i";
}

AComplex operator+(AComplex a, const AComplex& b) { return a += b; }
AComplex operator-(AComplex a, const AComplex& b) { return a -= b; }

TComplex operator*(const AComplex& a, const AComplex& b) { return TComplex(a) * TComplex(b); }
TComplex operator/(const AComplex& a, const AComplex& b) { return TComplex(a) / TComplex(b); }

void TComplex::normalize()
{
    if (_r < 0) _r = std::abs(_r);
    _phi = std::fmod(_phi, 2 * M_PI);
    if (_phi < 0) _phi += 2 * M_PI;
}

TComplex::TComplex(const double r, const double phi) : _r(r), _phi(phi)
{
    if (_r < 0) throw std::invalid_argument("Module cannot be negative");
    normalize();
    _count++;
#ifndef NDEBUG
    std::cout << "Created TComplex\n";
#endif
}

TComplex::TComplex(const AComplex& a)
{
    _r   = std::hypot(a.re(), a.im());
    _phi = std::atan2(a.im(), a.re());
    normalize();
    _count++;
#ifndef NDEBUG
    std::cout << "Converted: AComplex -> TComplex\n";
#endif
}

TComplex::TComplex(const TComplex& a) : _r(a._r), _phi(a._phi) { _count++; }

TComplex& TComplex::operator=(const TComplex& a) &
{
    if (this != &a) { _r = a._r; _phi = a._phi; }
    return *this;
}

TComplex::~TComplex() { _count--; }

TComplex& TComplex::operator*=(const TComplex& a) &
{
    _r   *= a._r;
    _phi += a._phi;
    normalize();
    return *this;
}

TComplex& TComplex::operator/=(const TComplex& a) &
{
    if (a._r == 0) throw std::runtime_error("Division by zero in TComplex");
    _r   /= a._r;
    _phi -= a._phi;
    normalize();
    return *this;
}

TComplex& TComplex::operator+=(const TComplex& a) &
{
    AComplex ac(*this);
    ac += AComplex(a);
    *this = TComplex(ac);
    return *this;
}

TComplex& TComplex::operator-=(const TComplex& a) &
{
    AComplex ac(*this);
    ac -= AComplex(a);
    *this = TComplex(ac);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TComplex& a)
{
    return os << "Module - " << a.r() << ", argument(angle) " << a.phi();
}

TComplex operator*(TComplex a, const TComplex& b) { return a *= b; }
TComplex operator/(TComplex a, const TComplex& b) { return a /= b; }

AComplex operator+(const TComplex& a, const TComplex& b) { return AComplex(a) + AComplex(b); }
AComplex operator-(const TComplex& a, const TComplex& b) { return AComplex(a) - AComplex(b); }

AComplex operator+(const TComplex& a, const AComplex& b) { return AComplex(a) + b; }
AComplex operator-(const TComplex& a, const AComplex& b) { return AComplex(a) - b; }

AComplex operator+(const AComplex& a, const TComplex& b) { return a + AComplex(b); }
AComplex operator-(const AComplex& a, const TComplex& b) { return a - AComplex(b); }

TComplex operator*(const TComplex& a, const AComplex& b) { return a * TComplex(b); }
TComplex operator/(const TComplex& a, const AComplex& b) { return a / TComplex(b); }

TComplex operator*(const AComplex& a, const TComplex& b) { return TComplex(a) * b; }
TComplex operator/(const AComplex& a, const TComplex& b) { return TComplex(a) / b; }

AComplex operator+(const double s, const AComplex& a) { return AComplex(s) + a; }
AComplex operator-(const double s, const AComplex& a) { return AComplex(s) - a; }
TComplex operator*(const double s, const AComplex& a) { return TComplex(s) * TComplex(a); }
TComplex operator/(const double s, const AComplex& a) { return TComplex(s) / TComplex(a); }

AComplex operator+(const double s, const TComplex& t) { return AComplex(s) + AComplex(t); }
AComplex operator-(const double s, const TComplex& t) { return AComplex(s) - AComplex(t); }
TComplex operator*(const double s, const TComplex& t) { return TComplex(s) * t; }
TComplex operator/(const double s, const TComplex& t) { return TComplex(s) / t; }