// Developed by Pavlo Vus on 15.02.2026
#include "triangle.h"

Triangle::Point::Point(const double x, const double y) : _x(x), _y(y) { _count++; }

Triangle::Point::Point(const Point& p) : _x(p._x), _y(p._y) { _count++; }

Triangle::Point& Triangle::Point::operator=(const Point& p) &
{
    if (this == &p) return *this;
    _x = p._x;
    _y = p._y;
    return *this;
}
Triangle::Point::~Point() { _count--; }

std::ostream& operator<<(std::ostream& os, const Triangle::Point& p) { return os << "(" << p.x() << ", " << p.y() << ")"; }

Triangle::Segment::Segment(const Point& p1, const Point& p2) : _p1(&p1), _p2(&p2) { _count++; }

Triangle::Segment::Segment(const Segment& s) : _p1(s._p1), _p2(s._p2) { _count++; }

Triangle::Segment::~Segment() { _count--; }

Triangle::Point Triangle::Segment::midpoint() const
{
    return Point((_p1->x() + _p2->x()) / 2.0,(_p1->y() + _p2->y()) / 2.0);
}

std::ostream& operator<<(std::ostream& os, const Triangle::Segment& s) { return os << "[" << s.p1() << " - " << s.p2() << "]"; }

void Triangle::check_invariant(const Point& a, const Point& b, const Point& c)
{
    if (const double area =std::abs(a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) + c.x() * (a.y() - b.y())) / 2.0; area < 1e-9)
        throw std::invalid_argument("Точки трикутника не можуть лежати на одній прямій!");
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3) : _v1(v1), _v2(v2), _v3(v3)
{
    check_invariant(_v1, _v2, _v3);
    _count++;
}

Triangle::Triangle(const Triangle& t) : _v1(t._v1), _v2(t._v2), _v3(t._v3)
{
    if (t._base_a) _base_a = new Point(*t._base_a);
    if (t._base_b) _base_b = new Point(*t._base_b);
    if (t._base_c) _base_c = new Point(*t._base_c);
    _count++;
}

Triangle& Triangle::operator=(const Triangle& t) &
{
    if (this == &t) return *this;

    _v1 = t._v1;
    _v2 = t._v2;
    _v3 = t._v3;

    delete _base_a; _base_a = t._base_a ? new Point(*t._base_a) : nullptr;
    delete _base_b; _base_b = t._base_b ? new Point(*t._base_b) : nullptr;
    delete _base_c; _base_c = t._base_c ? new Point(*t._base_c) : nullptr;

    return *this;
}

Triangle::~Triangle()
{
    delete _base_a;
    delete _base_b;
    delete _base_c;
    _count--;
}

void Triangle::setV1(const Point& p)
{
    check_invariant(p, _v2, _v3);
    _v1 = p;
}

void Triangle::setV2(const Point& p)
{
    check_invariant(_v1, p, _v3);
    _v2 = p;
}

void Triangle::setV3(const Point& p)
{
    check_invariant(_v1, _v2, p);
    _v3 = p;
}

Triangle::Segment Triangle::median_to_a() const
{
    delete _base_a;
    _base_a = new Point(side_a().midpoint());
    return {_v1, *_base_a};
}

Triangle::Segment Triangle::median_to_b() const
{
    delete _base_b;
    _base_b = new Point(side_b().midpoint());
    return {_v2, *_base_b};
}

Triangle::Segment Triangle::median_to_c() const
{
    delete _base_c;
    _base_c = new Point(side_c().midpoint());
    return {_v3, *_base_c};
}