#ifndef __LIST__
#define __LIST__

#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T>
class List{

private:
    class Node{
        private:
            T data;
            Node* next;
            Node* prev;


            Node(const_reference value)
                :data(value),next(nullptr),prev(nullptr)
                        {}

    };


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


//Constructors and Destuctor
public:
    List();
    List(value_type);
    List(const List& rhv);
    List(List&& other);
    List(std::initializer_list<T> init);
    ~List();


//Assigments
public:
    List& operator=(const List& rhv);
    List& operator=(List&& rhv);


//Element access
public:
    value_type front() const;
    value_type back() const;


//Iterators
public:
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;


//Capacity
public:
    bool empty() const;
    size_type size() const;


//Modifiers
public:
    void clear();
    void insert(const_reference value,const_reference pos);
    void emplace(const_reference value,const_reference pos);
    void erase(const_reference pos);
    void push_back(const_reference value);
    void pop_back(); 
    void push_front(const_reference value);
    void pop_front();
    void resize(const_reference new_size,const_reference value = value_type{});
    void swap(const_reference value1,const_reference value2);


//Non-member functions
public:
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;
    bool operator<(const List& other) const;
    bool operator<=(const List& other) const;
    bool operator>(const List& other) const;
    bool operator>=(const List& other) const;


//Members
private:
    Node* head;
    Node* tail;
    size_type List_size;
};


/////////////////////////////////////////////////////////////////////

//Class Const_iterator

template<typename T>
class List<T>::const_iterator{

private:
    List<T>::Node* current;

//Constructors and Destructor
public:
    const_iterator() = default;
    explicit const_iterator(Node* node);
    const_iterator(const const_iterator& rhv) = default;
    const_iterator(const iterator& rhv) = default;
    ~const_iterator();

//Assigments
public:
    const_iterator operator=(const const_iterator& other) = default;
    const_iterator operator=(const iterator& other) = default;


//Operators
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

//Non-member functions
public:
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;        

};

/////////////////////////////////////////////////////////////////////

//Class iterator

template<typename T>
class List<T>::iterator{

private:
    List<T>::Node* current;


//Iterator ctor
public:
    iterator() = default;
    explicit iterator(Node* node);
    iterator(const iterator& rhv) = default;
    iterator(iterator&& rhv) = default;
    ~iterator();

//Assigmets
public:
    iterator& operator=(const iterator& other) = default;
    iterator& operator=(iterator&& other) noexcept = default;

//Operators
public:
    reference operator*();
    const_reference operator*() const;

    pointer operator->();
    const_pointer operator->() const;

    iterator& operator++();
    iterator operator++(int);
    iterator operator+(const int n) const;
    iterator& operator+=(const int n);

    iterator& operator--();
    iterator operator--(int);
    iterator operator-(const int n) const;
    iterator& operator-=(const int n);    


//Non-member functions
public:
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;

};


/////////////////////////////////////////////////////////////////////

//Class Const_Reverese_iterator

template<typename T>
class List<T>::const_reverse_iterator{

private:
    List<T>::Node* current;

//Constructors
public:
    const_reverse_iterator() = default;
    explicit const_reverse_iterator(Node* node);
    const_reverse_iterator(const const_reverse_iterator& rhv) = default;
    const_reverse_iterator(const reverse_iterator& rhv) = default;
    const_reverse_iterator(const_reverse_iterator&& rhv) noexcept = default;


//Assigmets
public:
    const_reverse_iterator& operator=(const const_reverse_iterator& rhv) = default;
    const_reverse_iterator operator=(const_reverse_iterator&& rhv) noexcept = default;


//Operators
public:
    const_reference operator*() const;
    const_pointer operator->() const;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator operator+(const int n) const;
    const_reverse_iterator& operator+=(const int n);

    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);
    const_reverse_iterator operator-(const int n) const;
    const_reverse_iterator& operator-=(const int n);


//Non-member functions
public:
    bool operator==(const const_reverse_iterator& other) const;
    bool operator!=(const const_reverse_iterator& other) const;

};


////////////////////////////////////////////////////////////////////////

//Class Reverse_Iterator

template<typename T>
class List<T>::reverse_iterator{

private:
    List<T>::Node* current;


//Constructors
public:
    reverse_iterator() = default;
    explicit reverse_iterator(Node* node);
    reverse_iterator(const reverse_iterator& rhv) = default;
    reverse_iterator(reverse_iterator&& rhv) = default;


//Assigments
public:
    reverse_iterator operator=(const reverse_iterator& rhv) = default;
    reverse_iterator operator=(reverse_iterator&& other) = default;

//Operators
public:
    reference operator*();
    const_reference operator*() const;

    pointer operator->();
    const_pointer operator->() const;

    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator operator+(const int n) const;
    reverse_iterator& operator+=(const int n);

    reverse_iterator& operator--();
    reverse_iterator operator--(int);
    reverse_iterator operator-(const int n) const;
    reverse_iterator& operator-=(const int n);


//Non-member functions  
public:
    bool operator==(const reverse_iterator& other) const;
    bool operator!=(const reverse_iterator& other) const;

};




#include "List.tpp"
#endif