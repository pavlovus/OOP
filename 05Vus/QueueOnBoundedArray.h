// Developed by Pavlo Vus on 16.04.2026
#pragma once
#include "IQueue.h"
#include <stdexcept>

template<typename T, std::size_t Capacity>
class QueueOnBoundedArray final : public IQueue<T>
{
    static_assert(Capacity >= 1, "Capacity має бути > 0");

    // Стратегія пам'яті: статичний масив T _buf[Cap]
    T _buf[Capacity];
    std::size_t _head = 0;
    std::size_t _tail = 0;
    std::size_t _size = 0;

public:
    //Rule of Zero
    QueueOnBoundedArray() = default;

    [[nodiscard]] bool empty() const override { return _size == 0; }
    [[nodiscard]] std::size_t size()  const override { return _size; }

    const T& front() const override
    {
        if (empty()) throw std::underflow_error("QueueOnBoundedArray: front() на порожній черзі");
        return _buf[_head];
    }

    void pop() override
    {
        if (empty()) throw std::underflow_error("QueueOnBoundedArray: pop() на порожній черзі");
        _head = (_head + 1) % Capacity;
        --_size;
    }

    void put(const T& value) override
    {
        if (_size == Capacity) throw std::overflow_error("QueueOnBoundedArray: черга переповнена");
        _buf[_tail] = value;
        _tail = (_tail + 1) % Capacity;
        ++_size;
    }

    bool peek(const std::size_t index, T& out) const override
    {
        if (index >= _size) return false;
        out = _buf[(_head + index) % Capacity];
        return true;
    }

    [[nodiscard]] static std::size_t capacity() noexcept { return Capacity; }
    [[nodiscard]] bool full() const noexcept { return _size == Capacity; }
};