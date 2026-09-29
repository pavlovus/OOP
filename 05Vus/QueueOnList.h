// Developed by Pavlo Vus on 16.04.2026
#pragma once
#include "IQueue.h"
#include <stdexcept>

template<typename T>
class QueueOnList final : public IQueue<T>
{
    // Стратегія пам'яті
    // кожен put() - new Node - динамічна алокація одного вузла
    // кожен pop() - звільнення рівно одного вузла
    // деструктор - робимо pop() всіх вузлів та звільняємо пам'ять
    struct Node
    {
        T _val;
        Node* _next = nullptr;
        explicit Node(const T& v) : _val(v) {}
    };

    Node* _front = nullptr;
    Node* _back  = nullptr;
    std::size_t _size  = 0;

    void clear() noexcept
    {
        while (_front) {
            Node* tmp = _front->_next;
            delete _front;
            _front = tmp;
        }

        _back = nullptr;
        _size = 0;
    }

public:
    // Rule of Five
    QueueOnList() = default;

    ~QueueOnList() override { clear(); }

    QueueOnList(const QueueOnList& o) : QueueOnList()
    {
        for (const Node* n = o._front; n; n = n->_next) put(n->_val);
    }

    QueueOnList(QueueOnList&& o) noexcept : _front(o._front), _back(o._back), _size(o._size)
    {
        o._front = o._back = nullptr;
        o._size  = 0;
    }

    QueueOnList& operator=(const QueueOnList& o)
    {
        if (this != &o) {
            QueueOnList tmp(o);
            swap(*this, tmp);
        }
        return *this;
    }

    QueueOnList& operator=(QueueOnList&& o) noexcept
    {
        if (this != &o) {
            clear();

            _front = o._front;
            _back  = o._back;
            _size  = o._size;

            o._front = nullptr;
            o._back  = nullptr;
            o._size  = 0;
        }
        return *this;
    }

    [[nodiscard]] bool empty() const override { return _size == 0; }
    [[nodiscard]] std::size_t size()  const override { return _size; }

    const T& front() const override
    {
        if (empty()) throw std::underflow_error("QueueOnList: front() на порожній черзі");
        return _front->_val;
    }

    void pop() override
    {
        if (empty()) throw std::underflow_error("QueueOnList: pop() на порожній черзі");

        const Node* old = _front;
        _front    = _front->_next;

        if (!_front) _back = nullptr;
        delete old;
        --_size;
    }

    void put(const T& value) override
    {
        Node* n = new Node(value);
        if (_back) _back->_next = n;
        else _front = n;

        _back = n;
        ++_size;
    }

    bool peek(const std::size_t index, T& out) const override
    {
        if (index >= _size) return false;

        const Node* n = _front;
        for (std::size_t i = 0; i < index; ++i)n = n->_next;
        out = n->_val;

        return true;
    }
};