// Developed by Pavlo Vus on 16.04.2026
#pragma once
#include <cstddef>

template<typename T>
class IQueue {
public:
    IQueue() = default;
    virtual ~IQueue() = default;

    [[nodiscard]] virtual bool empty() const = 0;
    virtual const T& front() const = 0;
    virtual void pop() = 0;
    virtual void put(const T& value) = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;

    // Додаткова реалізація підглядання через peek()
    virtual bool peek(std::size_t index, T& out) const = 0;

    IQueue(const IQueue&) = delete;
    IQueue& operator=(const IQueue&) = delete;
};