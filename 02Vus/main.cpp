// Developed by Pavlo Vus on 22.02.2026
#include <iostream>
#include <cassert>
#include "Complex.h"
using namespace std;

int main() {
    cout << "AComplex Operations: " << endl;
    AComplex a1(1, 1);
    AComplex a2(2, 2);

    cout << "a1 in TComplex: " << TComplex(a1) << endl;

    a2 += a1;
    cout << "a2 += a1: " << a2 << endl;

    a2 -= a1;
    cout << "a2 -= a1: " << a2 << endl;

    auto res_add = a1 + a2;
    assert(typeid(res_add) == typeid(AComplex));
    cout << "a1 + a2: " << res_add << endl;

    auto res_sub = a1 - a2;
    assert(typeid(res_sub) == typeid(AComplex));
    cout << "a1 - a2: " << res_sub  << endl;

    auto res_mul_a = a1 * a2;
    assert(typeid(res_mul_a) == typeid(TComplex));
    cout << "a1 * a2: " << res_mul_a << endl;

    auto res_div_a = a1 / a2;
    assert(typeid(res_div_a) == typeid(TComplex));
    cout << "a1 / a2: " << res_div_a << endl;

    cout << endl;

    cout << "TComplex Operations" << endl;
    TComplex t1(2, 0);
    TComplex t2(1, M_PI/2);

    cout << "t1 in AComplex: " << AComplex(t1) << endl;

    t2 *= t1;
    cout << "t2 *= t1: " << t2 << endl;

    t2 /= t1;
    cout << "t2 /= t1: " << t2 << endl;

    auto res_add_t = t1 + t2;
    assert(typeid(res_add_t) == typeid(AComplex));
    cout << "t1 + t2: " << res_add_t << endl;

    auto res_sub_t = t1 - t2;
    assert(typeid(res_sub_t) == typeid(AComplex));
    cout << "t1 - t2: " << res_sub_t << endl;

    auto res_mul_t = t1 * t2;
    assert(typeid(res_mul_t) == typeid(TComplex));
    cout << "t1 * t2: " << res_mul_t << endl;

    cout << endl;

    cout << "Scalar & AComplex" << endl;
    cout << "1 + a2: " << 1 + a2 << endl;
    cout << "4 / a2: " << 4 / a2 << endl;

    cout << endl;

    cout << "Scalar & TComplex" << endl;
    cout << "1 + t2: " << 1 + t2 << endl;
    cout << "3 * t2: " << 3 * t2 << endl;

    cout << endl;

    cout << "AComplex & TComplex Mixed" << endl;

    auto mix1 = t1 + a2;
    assert(typeid(mix1) == typeid(AComplex));
    cout << "t1 + a2: " << mix1 << endl;

    auto mix2 = t1 * a2;
    assert(typeid(mix2) == typeid(TComplex));
    cout << "t1 * a2: " << mix2 << endl;

    auto mix3 = a1 / t2;
    assert(typeid(mix3) == typeid(TComplex));
    cout << "a1 / t2: " << mix3 << endl;

    auto mix4 = a1 + t2;
    assert(typeid(mix4) == typeid(AComplex));
    cout << "a1 + t2: " << mix4 << endl;

    auto mix5 = a1 - t2;
    assert(typeid(mix5) == typeid(AComplex));
    cout << "a1 - t2: " << mix5 << endl;

    auto mix6 = t1 - a2;
    assert(typeid(mix6) == typeid(AComplex));
    cout << "t1 - a2: " << mix6 << endl;

    auto mix7 = t1 / a2;
    assert(typeid(mix7) == typeid(TComplex));
    cout << "t1 / a2: " << mix7 << endl;

    cout << endl;

    cout << "Exception Handling:" << endl;
    try { TComplex bad(-1, 0); }
    catch (const std::invalid_argument& e) { cout << "Caught: " << e.what() << endl; }

    try { TComplex(1, 0) / TComplex(0, 0); }
    catch (const std::runtime_error& e) { cout << "Caught: " << e.what() << endl; }
    
    return 0;
}