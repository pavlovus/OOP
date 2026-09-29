// Developed by Pavlo Vus on 16.04.2026
#pragma once
#include "Array.h"

template<typename T>
class Dictionary
{
    Array<T> _data;

    // Двійковий пошук по словнику
    std::size_t binary_search(const T& val) const noexcept
    {
        std::size_t lo = 0, hi = _data.size();

        while (lo < hi) {
            std::size_t mid = lo + (hi - lo) / 2;
            if (_data[mid] < val) lo = mid + 1;
            else hi = mid;
        }

        return lo;
    }

public:

    class Iterator
    {
        const Dictionary* _owner;
        std::size_t _idx;

    public:
        Iterator(const Dictionary* d, const std::size_t i) noexcept : _owner(d), _idx(i) {}

        const T& operator*() const { return (*_owner)[_idx]; }

        Iterator& operator++() noexcept { ++_idx; return *this; }

        bool operator==(const Iterator& o) const noexcept { return _owner == o._owner && _idx == o._idx; }

        bool operator!=(const Iterator& o) const noexcept { return !(*this == o); }
    };


    //  Rule of Five
    // Конструктор
    Dictionary() : _data(4) {}
    // Копіювальний конструктор
    Dictionary(const Dictionary&  o) : _data(o._data) {}
    // Move конструктор
    Dictionary(Dictionary&& o) noexcept : _data(std::move(o._data)) {}

    // Копіювальне присвоєння
    Dictionary& operator=(const Dictionary&  o) = default;

    // Move присвоєння
    Dictionary& operator=(      Dictionary&& o) noexcept
    {
        _data = std::move(o._data);
        return *this;
    }

    // Деструктор, _data.~Array() викликається автоматично
    ~Dictionary() = default;

    bool insert(const T& val)
    {
        std::size_t pos = binary_search(val);
        if (pos < _data.size() && _data[pos] == val) return false;
        _data.insert(pos, val);
        return true;
    }

    bool remove(const T& val)
    {
        std::size_t pos = binary_search(val);
        if (pos >= _data.size() || !(_data[pos] == val)) return false;
        _data.remove(pos);
        return true;
    }

    bool contain(const T& val) const
    {
        std::size_t pos = binary_search(val);
        return pos < _data.size() && _data[pos] == val;
    }

    void clear() noexcept { _data.clear(); }

    [[nodiscard]] std::size_t size()  const noexcept { return _data.size(); }
    [[nodiscard]] bool empty() const noexcept { return _data.empty(); }
    bool is_sorted()
    {
        for (std::size_t i = 1; i < size(); ++i) if (!(_data[i - 1] < _data[i])) return false;
        return true;
    }

    // Доступ за індексом
    const T& operator[](std::size_t i) const { return _data[i]; }

    Iterator begin() const noexcept { return Iterator(this, 0); }
    Iterator end() const noexcept { return Iterator(this, _data.size()); }

    //Рівність словників
    bool operator==(const Dictionary& o) const
    {
        if (_data.size() != o._data.size()) return false;
        for (std::size_t i = 0; i < _data.size(); ++i)
            if (!(_data[i] == o._data[i])) return false;
        return true;
    }

    bool operator!=(const Dictionary& o) const { return !(*this == o); }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Dictionary<T>& d)
{
    os << '[';
    bool first = true;
    for (const auto& item : d) {
        if (!first) os << ", ";
        os << item;
        first = false;
    }
    return os << ']';
}

// Об'єднання
template<typename T>
Dictionary<T> operator+(const Dictionary<T>& a, const Dictionary<T>& b)
{
    Dictionary<T> result(a);
    for (auto it = b.begin(); it != b.end(); ++it) result.insert(*it);
    return result;
}

// Перетин
template<typename T>
Dictionary<T> operator*(const Dictionary<T>& a, const Dictionary<T>& b) {
    Dictionary<T> result;
    for (auto it = a.begin(); it != a.end(); ++it) if (b.contain(*it)) result.insert(*it);
    return result;
}


template<typename T>
void copy(Dictionary<T>& dst, const Dictionary<T>& src) { dst = src; }

template<typename T>
void merge_into(Dictionary<T>& dst, Dictionary<T>&& src)
{
    for (auto it = src.begin(); it != src.end(); ++it) dst.insert(*it);
    src.clear();
}