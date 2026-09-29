// Developed by Pavlo Vus on 16.04.2026
#pragma once

template<typename T>
class Array
{
    std::size_t _size;
    std::size_t _capacity;
    T* _data;

    void reallocate(const std::size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < _size; ++i) newData[i] = std::move(_data[i]);
        delete[] _data;
        _data     = newData;
        _capacity = newCapacity;
    }

public:
    explicit Array(const std::size_t capacity = 4)
        : _size(0), _capacity(capacity > 0 ? capacity : 1), _data(new T[_capacity]) {}

    //Rule of Five

    // Копіювальний конструктор
    Array(const Array& o) : _size(o._size), _capacity(o._capacity), _data(new T[o._capacity])
    {
        for (std::size_t i = 0; i < _size; ++i)_data[i] = o._data[i];
    }

    // Move конструктор
    Array(Array&& o) noexcept : _size(o._size), _capacity(o._capacity), _data(o._data)
    {
        o._size = 0; o._capacity = 0; o._data = nullptr;
    }

    // Копіювальне присвоєння
    Array& operator=(const Array& o)
    {
        if (this == &o) return *this;
        delete[] _data;

        _size = o._size; _capacity = o._capacity;
        _data = new T[_capacity];
        for (std::size_t i = 0; i < _size; ++i)_data[i] = o._data[i];

        return *this;
    }

    // Move-присвоєння
    Array& operator=(Array&& o) noexcept
    {
        if (this == &o) return *this;
        delete[] _data;

        _size = o._size; _capacity = o._capacity; _data = o._data;
        o._size = 0; o._capacity = 0; o._data = nullptr;

        return *this;
    }

    // Деструктор
    ~Array() { delete[] _data; }


    // Вставка елемента на позицію n
    void insert(std::size_t n, const T& val)
    {
        if (n > _size) throw std::out_of_range("Array::insert");
        if (_size == _capacity) reallocate(_capacity * 2);
        for (std::size_t i = _size; i > n; --i) _data[i] = std::move(_data[i - 1]);
        _data[n] = val;
        ++_size;
    }

    // Видалення елемента на позиції n
    void remove(const std::size_t n)
    {
        if (n >= _size) throw std::out_of_range("Array::remove");
        for (std::size_t i = n; i + 1 < _size; ++i) _data[i] = std::move(_data[i + 1]);
        --_size;
    }

    // Очищення
    void clear() noexcept { _size = 0; }

    // Селектори
    T& operator[](std::size_t i)
    {
        if (i >= _size) throw std::out_of_range("Array::operator[]");
        return _data[i];
    }

    const T& operator[](std::size_t i) const
    {
        if (i >= _size) throw std::out_of_range("Array::operator[]");
        return _data[i];
    }

    [[nodiscard]] std::size_t size()  const noexcept { return _size; }
    [[nodiscard]] bool empty() const noexcept { return _size == 0; }
};