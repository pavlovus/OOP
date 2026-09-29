// Developed by Pavlo Vus on 08.03.2026
#include <iostream>
#include <cassert>
#include "String.h"
using namespace std;

int main() {
    cout << "Тестування конструкторів" << endl;
    const String s_default;
    assert(s_default.length() == 0);

    const String s_c("Hello");
    assert(strcmp(s_c.c_str(), "Hello") == 0);
    assert(s_c.length() == 5);

    const string stl_str = " World";
    const String s_stl(stl_str);
    assert(strcmp(s_stl.c_str(), " World") == 0);

    cout << "s_c: " << s_c << endl;

    cout << "\nТестування переміщення та копіювання" << endl;
    String s_copy = s_c;
    assert(strcmp(s_copy.c_str(), "Hello") == 0);

    String s_move = std::move(s_copy);
    assert(strcmp(s_move.c_str(), "Hello") == 0);
    assert(s_copy.length() == 0);

    cout << "s_move: " << s_move << endl;
    cout << "s_copy (після переміщення): " << (s_copy.length() == 0 ? "порожній" : s_copy.c_str()) << endl;

    cout << "\nТестування доступу []" << endl;
    s_move[0] = 'h';
    assert(s_move[0] == 'h');
    assert(strcmp(s_move.c_str(), "hello") == 0);
    cout << "s_move після заміни [0]: " << s_move << endl;

    cout << "\nТестування змішаних операцій (+)" << endl;
    String s1("My ");
    const string s2 = "name";
    const char* p = "is Pavlo";

    const String res1 = s1 + s2;
    assert(strcmp(res1.c_str(), "My name") == 0);
    cout << "s1 + s2: " << res1 << endl;

    const String res2 = String(s2) + s1;
    assert(strcmp(res2.c_str(), "nameMy ") == 0);
    cout << "s2 + s1: " << res2 << endl;

    const String res3 = p + s1;
    assert(strcmp(res3.c_str(), "is PavloMy ") == 0);
    cout << "p + s1: " << res3 << endl;

    const String res4 = s1 + p;
    assert(strcmp(res4.c_str(), "My is Pavlo") == 0);
    cout << "s1 + p: " << res4 << endl;

    cout << "\nСуміщене присвоєння (+=)" << endl;
    s1 += s2;
    assert(strcmp(s1.c_str(), "My name") == 0);

    s1 += " is Alex";
    assert(strcmp(s1.c_str(), "My name is Alex") == 0);
    cout << "s1 += ... : " << s1 << endl;

    cout << "\nЗведення до C-char" << endl;
    const char* c_ptr = s1;
    assert(strcmp(c_ptr, "My name is Alex") == 0);
    cout << "Зведений вказівник c_ptr: " << c_ptr << endl;

    cout << "\nОператори порівняння" << endl;
    const String cmp1("Same");
    const String cmp2("Same");
    const String cmp3("Different");

    assert(cmp1 == cmp2);
    assert(cmp1 != cmp3);
    cout << "cmp1 == cmp2: " << (cmp1 == cmp2 ? "true" : "false") << endl;
    cout << "cmp1 != cmp3: " << (cmp1 != cmp3 ? "true" : "false") << endl;

    return 0;
}