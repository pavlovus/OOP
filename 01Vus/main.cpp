// Developed by Pavlo Vus on 15.02.2026
#include "triangle.h"
#include <iostream>
#include <cassert>
using namespace std;

unsigned int Triangle::Point::_count   = 0;
unsigned int Triangle::Segment::_count = 0;
unsigned int Triangle::_count          = 0;

int main()
{
    cout << "Створення трикутника" << endl;
    const Triangle tri1(Triangle::Point(0,0), Triangle::Point(4,0), Triangle::Point(2,4));
    
    assert(Triangle::Point::count() == 3);
    assert(Triangle::count() == 1);
    cout << "Point створено: "    << Triangle::Point::count()   << " (очікується 3)" << endl;
    cout << "Triangle створено: " << Triangle::count()           << " (очікується 1)" << endl;

    cout << "Вершини" << endl;
    assert(tri1.v1().x() == 0 && tri1.v1().y() == 0);
    assert(tri1.v2().x() == 4 && tri1.v2().y() == 0);
    assert(tri1.v3().x() == 2 && tri1.v3().y() == 4);
    cout << "v1: " << tri1.v1() << ", v2: " << tri1.v2() << ", v3: " << tri1.v3() << endl;

    cout << "Сторони" << endl;
    // Сторони створюються лише при виклику — кожен виклик створює новий Segment
    const auto sa = tri1.side_a();
    const auto sb = tri1.side_b();
    const auto sc = tri1.side_c();

    assert(Triangle::Segment::count() == 3);
    cout << "Segment створено: " << Triangle::Segment::count() << " (очікується 3)" << endl;
    cout << "Сторона a: " << sa << endl;
    cout << "Сторона b: " << sb << endl;
    cout << "Сторона c: " << sc << endl;

    cout << "Медіани" << endl;
    // До виклику медіан — _base_a/b/c == nullptr, жодного зайвого Point не існує
    const unsigned int points_before = Triangle::Point::count();

    const auto med1 = tri1.median_to_a();
    const auto med2 = tri1.median_to_b();
    const auto med3 = tri1.median_to_c();

    // Кожна медіана виділяє рівно 1 новий Point для основи (new Point всередині)
    assert(Triangle::Point::count() == points_before + 3);
    // Ще 3 Segment для медіан
    cout << Triangle::Segment::count();
    assert(Triangle::Segment::count() == 6);

    cout << "Point після медіан: " << Triangle::Point::count() << " (очікується " << points_before + 3 << ")" << endl;
    cout << "Segment після медіан: " << Triangle::Segment::count() << " (очікується 6)" << endl;
    cout << "Медіана до a: " << med1 << endl;
    cout << "Медіана до b: " << med2 << endl;
    cout << "Медіана до c: " << med3 << endl;

    assert(med1.p2().x() == (tri1.v2().x() + tri1.v3().x()) / 2.0);
    assert(med1.p2().y() == (tri1.v2().y() + tri1.v3().y()) / 2.0);

    cout << "Повторний виклик median_to_a" << endl;
    const unsigned int points_before_repeat = Triangle::Point::count();
    const auto med1b = tri1.median_to_a();
    assert(Triangle::Point::count() == points_before_repeat);
    cout << "Point після повторного виклику: " << Triangle::Point::count() << " (без змін, очікується " << points_before_repeat << ")" << endl;

    cout << "Модифікатори вершин" << endl;
    Triangle tri_mut(Triangle::Point(0,0), Triangle::Point(3,0), Triangle::Point(0,3));
    tri_mut.setV1(Triangle::Point(1,0));
    assert(tri_mut.v1().x() == 1 && tri_mut.v1().y() == 0);
    cout << "Після setV1(1,0): v1 = " << tri_mut.v1() << endl;

    cout << "Копіювання" << endl;
    const Triangle tri_copy(tri1);
    assert(Triangle::count() == 3);
    cout << "Triangle після копіювання: " << Triangle::count() << " (очікується 3)" << endl;
    assert(&tri_copy.v1() != &tri1.v1());

    cout << "Присвоєння" << endl;
    Triangle tri_assign(Triangle::Point(1,0), Triangle::Point(5,0), Triangle::Point(3,4));
    tri_assign = tri1;
    assert(tri_assign.v1().x() == tri1.v1().x());
    assert(tri_assign.v2().y() == tri1.v2().y());

    tri_assign = tri_assign;
    assert(tri_assign.v1().x() == tri1.v1().x());

    cout << "Інваріант" << endl;

    try {
        Triangle bad(Triangle::Point(0,0), Triangle::Point(1,1), Triangle::Point(2,2));
        assert(false);
    } catch (const invalid_argument& e) { cout << "Виняток при колінеарних точках: " << e.what() << endl; }

    try {
        Triangle tri_inv(Triangle::Point(0,0), Triangle::Point(3,0), Triangle::Point(0,3));
        tri_inv.setV3(Triangle::Point(3,0));
        assert(false);
    } catch (const invalid_argument& e) { cout << "Виняток при намаганні зробити одну з вершин колінеарною: " << e.what() << endl; }

    cout << "Підсумок лічильників" << endl;
    cout << "Всього Point створено: " << Triangle::Point::count()   << endl;
    cout << "Всього Segment створено: " << Triangle::Segment::count() << endl;
    cout << "Всього Triangle створено: " << Triangle::count()         << endl;

    cout << "Усі тести пройдено успішно" << endl;
    return 0;
}