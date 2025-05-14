#ifndef __Queue__
#define __Queue__

#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>


template <typename T>
class Queue {

    private:
        std::vector<T> data;

    //Member types
    public:
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using rvalue_reference = value_type&&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const pointer;

    //Constructors
    public:
        Queue();
        Queue(size_type count, const_reference value);
        Queue(const Queue& other);
        Queue(Queue&& other);
        Queue(std::initializer_list<T> init);
        ~Queue();

    //Member functions
    public:
        Queue& operator= (const Queue& rhv);
        Queue& operator= (Queue&& rhv);

    //Element access
    public:
        reference front();
        const_reference front() const;

        reference back();
        const_reference back() const;

    //Capacity
    public:
        bool empty() const;
        size_type size() const;

    //Modifiers
    public:
        void push(const_reference value);
        void push(rvalue_reference value);

        void pop();

        void swap(Queue& other) noexcept;

    //Non-member functions
    bool operator==(const Queue& rhv) const;
    bool operator!=(const Queue& rhv) const;
    bool operator<(const Queue& rhv) const;
    bool operator<=(const Queue& rhv) const;
    bool operator>(const Queue& rhv) const;
    bool operator>=(const Queue& rhv) const;
};

#endif