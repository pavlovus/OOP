// Developed by Pavlo Vus on 29.03.2026
#pragma once
#include "Array.h"

template<typename T, template<typename> class Storage = Array>
class Sequence {
    Storage<T> _storage;

    void append(Array<T>& s, const T& x) { s.push_back(x); }
    void append(ForwardList<T>& s, const T& x) { s.push_front(x); }

    std::size_t get_capacity(const Array<T>& s) const { return s.capacity(); }
    std::size_t get_capacity(const ForwardList<T>& s) const { return s.size(); }

public:
    Sequence() = default;

    void append(const T& x) { append(_storage, x); }

    bool remove(const T& x) { return _storage.remove_first(x); }

    bool contains(const T& x) const { return _storage.contains(x); }

    [[nodiscard]] std::size_t size() const { return _storage.size(); }

    [[nodiscard]] bool empty() const { return _storage.empty(); }

    [[nodiscard]] std::size_t capacity() const { return get_capacity(_storage); }

};