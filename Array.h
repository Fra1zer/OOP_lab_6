#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Array {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    unsigned int Count;

public:
    class Iterator {
        Node* ptr;
    public:
        friend class Array;
        Iterator(Node* p = nullptr) : ptr(p) {}

        Iterator& operator++() {
            if (!ptr)
                return *this;
            ptr = ptr->next;
            return *this;
        
        }

        Iterator& operator--() {
            if (!ptr)
                return *this;
            ptr = ptr->prev;
            return *this;
        }

        T& operator*() const {
            if (!ptr)
                throw std::runtime_error("Dereferencing null iterator");
            return ptr->value;
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };

    Array() : head(nullptr), tail(nullptr), Count(0) {}

    Array(const Array& other) : Array() {
        for (auto it = other.begin(); it != other.end(); ++it)
            push_back(*it);
    }

    ~Array() { clear(); }

    Array& operator=(const Array& other) {
        if (this != &other) {
            clear();
            for (auto it = other.begin(); it != other.end(); ++it)
                push_back(*it);
        }
        return *this;
    }

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

    
    bool empty() const { return Count == 0; }
    unsigned int size() const { return Count; }

    T& front() { return head->value; }
    T& back() { return tail->value; }

    void clear() {
        while (!empty())
            pop_back();
    }

    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        ++Count;
    }

    void pop_back() {
        if (!tail) return;

        Node* tmp = tail;
        tail = tail->prev;

        if (tail) tail->next = nullptr;
        else head = nullptr;

        delete tmp;
        --Count;
    }

    void swap(Array& other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(Count, other.Count);
    }

    friend std::istream& operator>>(std::istream& in, Array& lst) {
        lst.clear();
        size_t size;
        in >> size;
        T value;
        for (size_t i = 0; i < size; ++i)
        {
            if (!(in >> value))
            {
                lst.clear();
                return in;
            }
            lst.push_back(value);
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Array& lst) {
        out << lst.size();
        Node* it = lst.head;
        while (it != nullptr) {
            out << " " << it->value;
            it = it->next;
        }
        return out;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& list)
{
    typename Array<T>::Node* cur = list.head->next;
    out << list.size();
    while (cur != list.end())
    {
        out << " " << cur->value;
        cur = cur->next;
    }

    return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Array<T>& list)
{
    list.clear();
    size_t size;
    in >> size;
    T value;

    for (size_t i = 0; i < size; ++i)
    {
        if (!(in >> value))
        {
            list.clear();
            return in;
        }
        list.push_back(value);
    }
    return in;
}