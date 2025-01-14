#ifndef __DEQUE__
#define __DEQUE__

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <vector>


template <typename T>
class Deque {

    //Members
    private:
        static constexpr size_t Block_size = 5;
        std::vector<T*> blocks;
        size_t front_index;
        size_t back_index;
        size_t size;


    //Value Types
    public:
        using value_type = T;
        using size_type = size_t;
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


    //MEMBER FUNCTIONS

    //Constructors and Destructor    
    public:
        Deque ();
        explicit Deque (size_type count, const_reference value = T());
        Deque (const Deque& rhv);
        Deque (Deque&& other) noexcept;
        Deque (std::initializer_list<value_type> init);

        template <typename InputIterator>
        Deque (InputIterator First, InputIterator Last);

        ~Deque ();

    
        Deque& operator= (const Deque& other);
        Deque& opeartor= (Deque&& other) noexcept;
        Deque& operator= (std :: initializer_list<value_type> ilist);

        void assign (size_type count, const_reference value);
        void assign (std :: initializer_list<value_type> ilist);

        template <typename InputIt>
        void assign (InputIt First, inputIt Last);



    //ELEMENT ACCESS

    public:
        reference at (size_type pos);
        const_reference at (size_type pos) const;

        reference operator[] (size_type pos);
        const_reference operator[] (size_type pos) const;

        reference front ();
        const_reference front ();

        reference back ();
        const_reference back ();


    //ITERATORS

    public:
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const noexcept;


    //CAPACITY
    public:
        bool empty () const;
        size_type size () const;


    //MODIFIERS
    public:
        void clear ();

        iterator insert (const_iterator pos, const_reference value);
        iterator insert (const_iterator pos, value_type&& value);
        iterator insert (const_iterator pos, size_type count, const_reference value);

        template <typename InputIt>
        iterator insert (const_iterator pos, InputIt First, InputIt last);
        iterator insert (const_iterator pos, std::initializer_list<value_type ilist);

        iterator erase (const_iterator pos);
        iterator erase (const_iterator First, const_iterator Last);

        void push_back (const_reference value);
        void push_back (value_type&& value);

        void pop_front ();

        void resize (size_type count);
        void resize (size_type count, const_reference value);

        void swap (Deque& other);


    //NON-MEMBER FUNCTION
    public:
        bool operator== (const Deque& other) const;
        bool operator!= (const Deque& other) const;
        bool operator< (const Deque& other) const;
        bool operator<= (const Deque& other) const;
        bool operator> (const Deque& other) const;
        bool operator>= (const Deque& other) const;

};


//CONST_ITERATOR

template <typename T>
class Deque<T>::const_iterator {

    //CONSTRUCTORS
    private:
        const Deque* deque;
        size_t global_index;

    public:
        const_iterator() = default;
        const_iterator (const Deque* deque, size_t index);
        const_iterator(const const_iterator& rhv) = default;
        const_iterator(const_iterator&& rhv) noexcept = default;
        ~const_iterator() = default;

    //ASSIGMENT
    public:
        const_iterator operator= (const const_iterator& other) = default;
        const_iterator operator= (const_iterator&& other) = default;    


    //OPERATORS
    public:
        const_reference operator*() const;
        const_pointer operator->() const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator operator+(const int n) const;
        const_iterator& operator+=(int n);

        const_iterator& operator--();
        const_iterator operator--(int);
        const_iterator operator-(const int n) const;
        const_iterator& operator-=(const int n);


    //NON-MEMBER FUNCTION
    public:
        bool operator== (const const_iterator& other) const;
        bool operator!= (const const_iterator& other) const;
        bool operator< (const const_iterator& other) const;
        bool operator<= (const const_iterator& other) const;
        bool operator> (const const_iterator& other) const;
        bool operator>= (const const_iterator& other) const;   
};

#endif