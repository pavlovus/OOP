// Developed by Pavlo Vus on 16.04.2026
#include <iostream>
#include <cassert>
#include "IQueue.h"
#include "QueueOnBoundedArray.h"
#include "QueueOnList.h"
#include "QueueOnDynamicArray.h"

using namespace std;

void test_ififo(IQueue<int>& q, const string& name) {
    cout << name << "\n";

    assert(q.empty());
    assert(q.size() == 0);

    for (int i = 1; i <= 5; ++i) q.put(i);
    assert(!q.empty());
    assert(q.size() == 5);
    assert(q.front() == 1);

    for (int i = 1; i <= 5; ++i) {
        assert(q.front() == i);
        q.pop();
    }
    assert(q.empty());

    q.put(42);
    assert(q.front() == 42);
    q.pop();
    assert(q.empty());

    cout << "Тестування "<< name << " пройдено успішно\n";
}

void test_peek(IQueue<int>& q, const string& name) {
    cout << "peek: " << name << "\n";

    for (int i = 0; i < 5; i++) q.put(i);

    for (size_t i = 0; i < 5; i++) {
        int val = 0;
        const bool ok = q.peek(i, val);
        assert(ok);
        assert(val == i);
        cout << "peek[" << i << "] = " << val << "\n";
    }

    int val = 0;
    assert(!q.peek(5, val));
    cout << "peek за межами повертає false\n";

    q.pop();
    q.peek(0, val);
    assert(val == 1);
    cout << "peek[0] після pop() = " << val << "\n";

    while (!q.empty()) q.pop();
}

void test_polymorphic_dispatch() {
    cout << "Поліморфний виклик через IQueue<int>* \n";

    QueueOnBoundedArray<int, 32> bounded_array;
    QueueOnList<int> on_list;
    QueueOnDynamicArray<int> dynamic_array;

    IQueue<int>* queues[3] = { &bounded_array, &on_list, &dynamic_array };

    for (int q = 0; q < 3; ++q) for (int i = 1; i <= 4; ++i) queues[q]->put(i * 10);

    for (int q = 0; q < 3; ++q) {
        const char* names[3]  = { "BoundedArray", "List", "DynamicArray" };
        cout << names[q] << ": ";
        while (!queues[q]->empty()) {
            cout << queues[q]->front() << " ";
            queues[q]->pop();
        }
        cout << "\n";
    }
    cout << "Всі черги видали однаковий FIFO-порядок\n";
}


void test_overflow() {
    cout << "Тестування переповнення BoundedArray\n";
    QueueOnBoundedArray<int, 3> q;
    q.put(1); q.put(2); q.put(3);
    assert(q.full());

    bool threw = false;
    try { q.put(4); }
    catch (const overflow_error&) { threw = true; }
    assert(threw);
    cout << "overflow_error кидається при put() у повну чергу \n";
}

void test_dynamic_growth() {
    cout << "Тестування розширення та стискання DynamicArray\n";
    QueueOnDynamicArray<int> q(2);

    cout << "Ємність після 0 елементів: " << q.capacity() << "\n";
    for (int i = 0; i < 20; ++i) q.put(i);
    cout << "Ємність після 20 елементів: " << q.capacity() << "\n";
    assert(q.capacity() >= 20);

    while (q.size() > 2) q.pop();
    cout << "Ємність після скорочення:   " << q.capacity() << "\n";
    assert(q.capacity() < 20);
    cout << "Автоматичне стискання виконується\n";
}

static void test_copy_move_list() {
    cout << "Тестування copy і move семантик\n";

    QueueOnList<int> orig;
    for (int i = 1; i <= 5; ++i) orig.put(i);

    QueueOnList copied(orig);
    assert(copied.size() == 5);
    assert(orig.size()   == 5);
    for (int i = 1; i <= 5; ++i) {
        assert(orig.front()   == i);
        assert(copied.front() == i);
        orig.pop(); copied.pop();
    }
    assert(orig.empty() && copied.empty());
    cout << "Глибока копія працює (оригінал незалежний від копії)\n";

    QueueOnList<int> src;
    for (int i = 10; i <= 30; i += 10) src.put(i);

    const QueueOnList dst(std::move(src));
    assert(src.empty());
    assert(dst.size() == 3);
    assert(dst.front() == 10);
    cout << "Move-конструктор працює (src порожній після move)\n";
}

void test_unique_ptr_polymorphism() {
    cout << "Тестування unique_ptr<IQueue<int>> поліморфізму\n";

    unique_ptr<IQueue<int> > q = make_unique<QueueOnList<int> >();
    q->put(1); q->put(2); q->put(3);
    assert(q->size() == 3 && q->front() == 1);
    cout << "QueueOnList через unique_ptr працює\n";

    q = make_unique<QueueOnDynamicArray<int>>();
    q->put(7); q->put(8);
    assert(q->size() == 2 && q->front() == 7);
    cout << "QueueOnDynamicArray через unique_ptr працює\n";
}

int main() {
    cout << "QueueOnBoundedArray<int, 32>\n";
    QueueOnBoundedArray<int, 32> q1;
    test_ififo(q1, "BoundedArray FIFO");
    test_peek(q1, "BoundedArray peek");
    test_overflow();
    cout << "\n";

    cout << "QueueOnList<int>\n";
    QueueOnList<int> q2;
    test_ififo(q2, "QueueOnList FIFO");
    test_peek(q2, "QueueOnList peek");
    test_copy_move_list();
    cout << "\n";

    cout << "QueueOnDynamicArray<int>\n";
    QueueOnDynamicArray<int> q3;
    test_ififo(q3, "DynamicArray FIFO");
    test_peek(q3, "DynamicArray peek");
    test_dynamic_growth();
    cout << "\n";

    cout << "Поліморфний виклик\n";
    test_polymorphic_dispatch();
    cout << "\n";

    cout << "unique_ptr<IQueue<int>>\n";
    test_unique_ptr_polymorphism();
    cout << "\n";

    return 0;
}