#ifndef __ARRAY__
#define __ARRAY__

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <compare>

template <typename T,std::size_t N>
class Array{

private:
    T arr[N];


//Member types
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;


//Iterators
public:
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;


//Constuctors
public:
    Array() = default;
    constexpr Array(std::initializer_list<T> init);


//Element access
public:
    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;

    constexpr reference front();
    constexpr const_reference front() const;

    constexpr reference back();
    constexpr const_reference back() const;

    constexpr pointer data() noexcept;
    constexpr const_pointer data() const noexcept;


//Iterators
public:
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;


//Capacity
public:
    constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;


//Operations
public:
    constexpr void fill(const_reference value);
    constexpr void swap(Array& other) noexcept;


//Non-member functions
public:
    constexpr bool operator==(const Array<T,N>& rhv) const;

};



///////////////////////////////////////////////////////////////////////////////////

//Class Const_Iterator
template<typename T,std::size_t N>
class Array<T,N>::const_iterator{

public:
    const_pointer ptr;


//Constructor
public:
    const_iterator() = default;
    explicit const_iterator(const_pointer p);
    const_iterator(const const_iterator& other) = default;
    const_iterator(const_iterator&& other) = default;
    ~const_iterator() = default;


//Assigment
public:
    const_iterator& operator=(const const_iterator& otehr) = default;
    const_iterator& operator=(const_iterator&& other) = default;


//Operators
public:
    const_reference operator*() const;
    const_pointer operator->() const;

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator operator+(const size_type n) const;

    const_iterator& operator--();
    const_iterator operator--(int);
    const_iterator operator-(const size_type n) const;


//Non-member functions
public:
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool operator<(const const_iterator& other) const;
    bool operator<=(const const_iterator& other) const;
    bool operator>(const const_iterator& other) const;
    bool operator>=(const const_iterator& other) const;

};




//////////////////////////////////////////////////////////////////////////////////////

//Class Iterator
template<typename T,std::size_t N>
class Array<T,N>::iterator{

private:
    pointer ptr;

//Constructors
public:
    iterator() = default;
    constexpr iterator(const pointer p);
    iterator(const iterator& other) = default;
    iterator(iterator&& other) = default;
    ~iterator() =  default;

//Assigments
public:
    iterator& operator=(const iterator& rhv) = default;
    iterator& operator=(iterator&& rhv) = default;


//Operators
public:    
    reference operator*() const;
    pointer operator->() const;

    iterator& operator++();
    iterator operator++(int);
    iterator operator+(const size_type n) const;

    iterator& operator--();
    iterator operator--(int);
    iterator operator-(const size_type n) const;


//Non-member functions
public:
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    bool operator>(const iterator& other) const;
    bool operator>=(const iterator& other) const;
    bool operator<(const iterator& other) const;;
    bool operator<=(const iterator& other) const;

};



////////////////////////////////////////////////////////////////////////////////////

//Class Const Reverse Iterator
template<typename T,std::size_t N>
class Array<T,N>::const_reverse_iterator{

private:
    const_pointer ptr;


//Constructors
public:
    const_reverse_iterator() = default;
    constexpr const_reverse_iterator(const pointer p);
    const_reverse_iterator(const const_reverse_iterator& other) = default;
    const_reverse_iterator(const_reverse_iterator&& other) = default;
    ~const_reverse_iterator() = default;


//Assigments
public:
    const_reverse_iterator& operator=(const const_reverse_iterator& rhv) = default;
    const_reverse_iterator operator=(const_reverse_iterator&& rhv) = default;


//Operators
public:
    const_reference operator*() const;
    const_pointer operator->() const;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator operator+(const size_type n) const;

    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);
    const_reverse_iterator operator-(const size_type n) const;


//Non-member types
public:
    bool operator==(const const_reverse_iterator& other) const;
    bool operator!=(const const_reverse_iterator& other) const;
    bool operator>(const const_reverse_iterator& other) const;
    bool operator>=(const const_reverse_iterator& other) const;
    bool operator<(const const_reverse_iterator& other) const;
    bool operator<=(const const_reverse_iterator& other) const;

}; 


///////////////////////////////////////////////////////////////////////////////

//Class Reverse Iterator
template<typename T,std::size_t N>
class Array<T,N>::reverse_iterator{

private:
    pointer ptr;


//Constructor
public:
    reverse_iterator() = default;
    constexpr reverse_iterator(const pointer p);
    reverse_iterator(const reverse_iterator& other) = default;
    reverse_iterator(reverse_iterator&& other) = default;
    ~reverse_iterator() = default;


//Assigments
public:
    reverse_iterator& operator=(const reverse_iterator& rhv) = default;
    reverse_iterator& operator=(reverse_iterator&& rhv) = default;


//Operators
public:
    reference operator*() const;
    pointer operator->() const;

    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator operator+(const size_type n) const;

    reverse_iterator& operator--();
    reverse_iterator operator--(int);
    reverse_iterator operator-(const size_type n) const;


//Non-member types
public:
    bool operator==(const reverse_iterator& other) const;
    bool operator!=(const reverse_iterator& other) const;
    bool operator>(const reverse_iterator& other) const;
    bool operator>=(const reverse_iterator& other) const;
    bool operator<(const reverse_iterator& other) const;
    bool operator<=(const reverse_iterator& other) const;

};

#include "array.tpp"
#endif

