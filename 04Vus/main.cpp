// Developed by Pavlo Vus on 29.03.2026
#include <iostream>
#include <string>
#include <cassert> // Бібліотека для assert

// Підключаємо ваші класи
#include "Array.h"
#include "ForwardList.h"
#include "Sequence.h"

using namespace std;

void test_int_sequence_array()
{
    cout << "Тестування Sequence<int, Array>" << endl;
    Sequence<int, Array> seq_arr;

    assert(seq_arr.empty());
    assert(seq_arr.size() == 0);
    assert(seq_arr.capacity() == 0);

    assert(seq_arr.capacity() == 0);

    for (int i = 0; i < 6; ++i) seq_arr.append(i);

    assert(!seq_arr.empty());
    assert(seq_arr.size() == 6);
    assert(seq_arr.capacity() >= 6);

    assert(seq_arr.contains(5) == true);
    assert(seq_arr.contains(99) == false);

    seq_arr.remove(3);
    assert(seq_arr.size() == 5);
    assert(seq_arr.contains(3) == false);

    cout << "Усі assert для Sequence<int, Array> пройдено успішно!" << endl << endl;
}

void test_int_sequence_forwardList()
{
    cout << "Тестування Sequence<int, ForwardList>" << endl;
    Sequence<int, ForwardList> seq_list;

    assert(seq_list.empty());
    assert(seq_list.size() == 0);
    assert(seq_list.capacity() == 0);

    for (int i = 1; i <= 6; ++i) seq_list.append(i );

    assert(!seq_list.empty());
    assert(seq_list.size() == 6);
    assert(seq_list.capacity() == 6);

    assert(seq_list.contains(5) == true);
    assert(seq_list.contains(99) == false);

    seq_list.remove(4);
    assert(seq_list.size() == 5);
    assert(seq_list.contains(4) == false);

    cout << "Усі assert для Sequence<int, ForwardList> пройдено успішно!" << endl << endl;
}

void test_string_sequence_array()
{
    cout << "Тестування Sequence<string, Array>" << endl;
    Sequence<string, Array> seq_str;

    assert(seq_str.empty());
    assert(seq_str.size() == 0);
    assert(seq_str.capacity() == 0);

    seq_str.append("Вус");
    seq_str.append("Павло");
    seq_str.append("Ігорович");
    seq_str.append("Іпз");
    seq_str.append("6 група");
    seq_str.append("ООП");

    assert(!seq_str.empty());
    assert(seq_str.size() == 6);
    assert(seq_str.capacity() >= 6);
    assert(seq_str.contains("Павло") == true);
    assert(seq_str.contains("Степан") == false);

    seq_str.remove("Ігорович");

    assert(seq_str.size() == 5);
    assert(seq_str.contains("Ігорович") == false);

    cout << "Усі assert для Sequence<string, Array> пройдено успішно!" << endl << endl;
}

void test_string_sequence_forwardList()
{
    cout << "Тестування Sequence<string, ForwardList>" << endl;
    Sequence<string, ForwardList> seq_str;

    assert(seq_str.empty());

    seq_str.append("Вус");
    seq_str.append("Павло");
    seq_str.append("Ігорович");
    seq_str.append("Іпз");
    seq_str.append("6 група");
    seq_str.append("ООП");

    assert(!seq_str.empty());
    assert(seq_str.size() == 6);
    assert(seq_str.capacity() == 6);
    assert(seq_str.contains("Павло") == true);
    assert(seq_str.contains("Степан") == false);

    seq_str.remove("Ігорович");

    assert(seq_str.size() == 5);
    assert(seq_str.contains("Ігорович") == false);

    cout << "Усі assert для Sequence<string, ForwardList> пройдено успішно!" << endl << endl;
}

int main()
{
    test_int_sequence_array();
    test_int_sequence_forwardList();
    test_string_sequence_array();
    test_string_sequence_forwardList();

    cout << "Всі тести успішно пройдено" << endl;
    return 0;
}