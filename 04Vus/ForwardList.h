// Developed by Pavlo Vus on 29.03.2026
#pragma once
#include <cstddef>

// ============================================================
//  ForwardList<T> -- singly linked list
//
//  Provided for Project 04 (Sequence).
//  Full doubly linked list with sentinel -- topic of later lectures.
// ============================================================
template<typename T>

class ForwardList {
    struct Node {
        T     _value;
        Node* _next;
        Node(const T& v, Node* n) : _value(v), _next(n) {}
    };

    Node*       _head;
    std::size_t _size;

public:
    ForwardList() : _head(nullptr), _size(0) {}

    ~ForwardList() {
        while (_head) {
            Node* tmp = _head->_next;
            delete _head;
            _head = tmp;
        }
    }

    ForwardList(const ForwardList&)            = delete;
    ForwardList& operator=(const ForwardList&) = delete;

    // ---- State ----
    [[nodiscard]] std::size_t size()  const { return _size; }
    [[nodiscard]] bool        empty() const { return _head == nullptr; }

    // ---- Modification ----

    // Prepend element (O(1)).
    // Note: iteration order is reverse of insertion order.
    void push_front(const T& x) {
        _head = new Node(x, _head);
        ++_size;
    }

    // Remove first occurrence of x.
    // Returns true if found and removed.
    // Implement yourself.
    bool remove_first(const T& x)
    {
        Node* prev = nullptr;
        Node* curr = _head;

        while (curr) {
            if (curr->_value == x) {
                if (prev) prev->_next = curr->_next;
                else _head = curr->_next;

                delete curr;
                --_size;
                return true;
            }

            prev = curr;
            curr = curr->_next;
        }
        return false;
    }

    // Check membership.
    // Implement yourself.
    bool contains(const T& x) const
    {
        Node* curr = _head;

        while (curr) {
            if (curr->_value == x) return true;
            curr = curr->_next;
        }

        return false;
    }

    // ---- Iterator (forward only) ----
    struct Iterator {
        Node* _node;

        const T&  operator*()  const { return _node->_value; }
        Iterator& operator++()       { _node = _node->_next; return *this; }
        bool operator!=(const Iterator& o) const { return _node != o._node; }
    };

    Iterator begin() const { return { _head };   }
    Iterator end()   const { return { nullptr }; }
};