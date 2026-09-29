// Developed by Pavlo Vus on 29.03.2026
#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>

// ============================================================
//  Array<T> -- dynamic array with fixed interface
//
//  Provided for Project 4 (Sequence).
//  Copy is disabled -- implement later.
// ============================================================
template<typename T>

class Array {
public:
    // Creates empty array (no memory allocated)
    explicit Array(std::size_t capacity = 0)
        : _capacity(capacity)
        , _size(0)
        , _data(capacity ? new T[capacity] : nullptr)
    {}

    ~Array() { delete[] _data; }

    Array(const Array&)            = delete;
    Array& operator=(const Array&) = delete;

    // ---- State ----
    [[nodiscard]] std::size_t size()     const { return _size; }
    [[nodiscard]] std::size_t capacity() const { return _capacity; }
    [[nodiscard]] bool        empty()    const { return _size == 0; }

    // ---- Access ----
    const T& operator[](std::size_t i) const {
        if (i >= _size)
            throw std::out_of_range("Array: index " + std::to_string(i)
                                    + " >= size " + std::to_string(_size));
        return _data[i];
    }

    // ---- Modification ----

    // Append element at the end.
    // Calls _grow() automatically if full.
    // Implement yourself.
    void push_back(const T& x)
    {
        if (_size == _capacity) _grow();
        _data[_size++] = x;
    }

    // Remove first occurrence of x.
    // Returns true if found and removed.
    // Implement yourself.
    bool remove_first(const T& x)
    {
        for (std::size_t i = 0; i < _size; ++i) {
            if (_data[i] == x) {
                for (std::size_t j = i; j < _size - 1; ++j) {
                    _data[j] = _data[j + 1];
                }
                --_size;
                return true;
            }
        }
        return false;
    }

    // Check membership.
    // Implement yourself.
    bool contains(const T& x) const
    {
        for (std::size_t i = 0; i < _size; ++i) if (_data[i] == x) return true;
        return false;
    }

private:
    std::size_t _capacity;
    std::size_t _size;
    T*          _data;

    // Grow capacity: new_capacity = 2 * _capacity + 1
    // Allocate new memory, move elements, free old.
    // Implement yourself.
    void _grow()
    {
        const std::size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2 + 1;
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < _size; ++i) new_data[i] = _data[i];

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
};