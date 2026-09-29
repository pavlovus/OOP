// Developed by Pavlo Vus on 16.04.2026
#pragma once
#include "IQueue.h"
#include <stdexcept>

template<typename T>
class QueueOnDynamicArray final : public IQueue<T>
{
    // Стратегія пам'яті:
    // при переповненні: new T[cap*2], переміщення елементів, delete[]
    // якщо заповненість < 25%: звільняємо зайвий буфер (скорочуємо на 50%)
    // деструктор - delete[] _buf
    T* _buf = nullptr;
    std::size_t _capacity = 0;
    std::size_t _head = 0;
    std::size_t _tail = 0;
    std::size_t _size = 0;

    void reallocate(const std::size_t newCap)
    {
        T* nd = new T[newCap];
        for (std::size_t i = 0; i < _size; ++i) nd[i] = std::move(_buf[(_head + i) % _capacity]);
        delete[] _buf;
        _buf = nd;
        _capacity = newCap;
        _head = 0;
        _tail = _size;
    }

public:
    // Rule of Five
    explicit QueueOnDynamicArray(const std::size_t initCap = 4)
        : _buf(new T[initCap > 0 ? initCap : 1]), _capacity(initCap > 0 ? initCap : 1) {}

    ~QueueOnDynamicArray() override { delete[] _buf; }

    QueueOnDynamicArray(const QueueOnDynamicArray& o) : _buf(new T[o._capacity]) , _capacity(o._capacity)
        , _tail(o._size), _size(o._size)
    {
        for (std::size_t i = 0; i < _size; ++i) _buf[i] = o._buf[(o._head + i) % o._capacity];
    }

    QueueOnDynamicArray(QueueOnDynamicArray&& o) noexcept : _buf(o._buf), _capacity(o._capacity)
        , _head(o._head), _tail(o._tail), _size(o._size)
    {
        o._buf = nullptr; o._capacity = o._head = o._tail = o._size = 0;
    }

    QueueOnDynamicArray& operator=(const QueueOnDynamicArray& o)
    {
        if (this == &o) return *this;
        delete[] _buf;
        _capacity = o._capacity;
        _buf = new T[_capacity];
        _size = o._size;
        _head = 0;
        _tail = _size;
        for (std::size_t i = 0; i < _size; ++i) _buf[i] = o._buf[(o._head + i) % o._capacity];
        return *this;
    }

    QueueOnDynamicArray& operator=(QueueOnDynamicArray&& o) noexcept
    {
        if (this == &o) return *this;
        delete[] _buf;
        _buf = o._buf; _capacity = o._capacity;
        _head = o._head; _tail = o._tail; _size = o._size;
        o._buf = nullptr; o._capacity = o._head = o._tail = o._size = 0;
        return *this;
    }

    [[nodiscard]] bool empty() const override { return _size == 0; }
    [[nodiscard]] std::size_t size() const override { return _size; }

    const T& front() const override
    {
        if (empty()) throw std::underflow_error("QueueOnDynamicArray: front() на порожній черзі");
        return _buf[_head];
    }

    void pop() override
    {
        if (empty()) throw std::underflow_error("QueueOnDynamicArray: pop() на порожній черзі");
        _head = (_head + 1) % _capacity;
        --_size;

        if (_size > 0 && _size <= _capacity / 4 && _capacity > 4) reallocate(_capacity / 2);
    }

    void put(const T& value) override
    {
        if (_size == _capacity) reallocate(_capacity * 2);
        _buf[_tail] = value;
        _tail = (_tail + 1) % _capacity;
        ++_size;
    }

    bool peek(const std::size_t index, T& out) const override
    {
        if (index >= _size) return false;
        out = _buf[(_head + index) % _capacity];
        return true;
    }

    [[nodiscard]] std::size_t capacity() const noexcept { return _capacity; }
};