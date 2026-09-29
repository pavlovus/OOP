// Developed by Pavlo Vus on 15.02.2026
#pragma once
#include <iostream>

class Triangle
{

public:

    class Point
    {
        double _x = 0, _y = 0;
        // Лічильник саме існуючих об'єктів, можна прибрати _count-- з деструкторів і
        // тоді це буде лічильник всіх створюваних об'єктів Point, але мені здалось більш логічним вести лічильник саме тих об'єктів,ʼ
        // які існують в пам'яті, а не просто створювались
        static unsigned int _count;
    public:
        explicit Point(double x = 0, double y = 0);
        Point(const Point& p);
        Point& operator=(const Point& p) &;
        ~Point();

        [[nodiscard]] double x() const { return _x; }
        [[nodiscard]] double y() const { return _y; }
        void setX(const double x) { _x = x; }
        void setY(const double y) { _y = y; }

        static unsigned int count() { return _count; }
    };

    class Segment
    {
        const Point* _p1;
        const Point* _p2;
        // Лічильник саме створюваних (не тих, що зараз існують) об'єктів Segment
        static unsigned int _count;
    public:
        Segment(const Point& p1, const Point& p2);
        Segment(const Segment& s);
        ~Segment();

        [[nodiscard]] const Point& p1() const { return *_p1; }
        [[nodiscard]] const Point& p2() const { return *_p2; }
        [[nodiscard]] Point midpoint() const;

        static unsigned int count() { return _count; }
    };

private:
    Point _v1, _v2, _v3;

    mutable Point* _base_a = nullptr;
    mutable Point* _base_b = nullptr;
    mutable Point* _base_c = nullptr;
    // Лічильник саме створюваних (не тих, що зараз існують) об'єктів Triangle
    static unsigned int _count;

    static void check_invariant(const Point& a, const Point& b, const Point& c);

public:
    Triangle(const Point& v1, const Point& v2, const Point& v3);
    Triangle(const Triangle& t);
    Triangle& operator=(const Triangle& t) &;
    ~Triangle();

    [[nodiscard]] const Point& v1() const { return _v1; }
    [[nodiscard]] const Point& v2() const { return _v2; }
    [[nodiscard]] const Point& v3() const { return _v3; }

    void setV1(const Point& p);
    void setV2(const Point& p);
    void setV3(const Point& p);

    [[nodiscard]] Segment side_a() const { return {_v2, _v3}; }
    [[nodiscard]] Segment side_b() const { return {_v1, _v3}; }
    [[nodiscard]] Segment side_c() const { return {_v1, _v2}; }

    [[nodiscard]] Segment median_to_a() const;
    [[nodiscard]] Segment median_to_b() const;
    [[nodiscard]] Segment median_to_c() const;

    static unsigned int count() { return _count; }
};

std::ostream& operator<<(std::ostream& os, const Triangle::Point& p);
std::ostream& operator<<(std::ostream& os, const Triangle::Segment& s);