#ifndef __LIST__
#define __LIST__

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <utility>

template <typename T>
class List{

private:
    class Node{
        public:
            using value_type = T;
            using size_type = std::size_t; 
            using reference = T&;
            using const_reference = const T&;
            using pointer = T*;
            using const_pointer = const T*;
        public:
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
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;


//Iterators
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


//Capacity
public:
    bool empty() const;
    size_type size() const;


//Modifiers
public:
    void clear();
    
    iterator insert(const_iterator pos,const_reference value);
    iterator insert(const_iterator pos,value_type&& value);
    iterator insert(const_iterator pos,size_type count, const_reference value);
    iterator insert(const_iterator pos,std::initializer_list<value_type> init);
    
    template<typename InputIt>
    iterator insert(const_iterator pos,InputIt first,InputIt last);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first,const_iterator last);

    void push_back(const_reference value);
    void push_back(value_type&& value);

    void pop_back(); 

    void push_front(const_reference value);
    void push_front(value_type&& value);

    void pop_front();

    void resize(size_type new_size);
    void resize(size_type new_size,const_reference value);

    void swap(List& other);


//Operations
void merge(List& other);
void merge(List&& other);

template<typename Compare>
void merge(List& other,Compare comp);
template<typename Compare>
void merge(List&& other,Compare comp);


void splice(const_iterator pos,List& other);
void splice(const_iterator pos,List&& other);
void splice(const_iterator pos,List& other,const_iterator it);
void splice(const_iterator pos,List&& other,const_iterator it);
void splice(const_iterator pos,List& other,const_iterator first, const_iterator last);
void splice(const_iterator pos,List&& other,const_iterator first,const_iterator last);

size_type remove(const_reference value);

template< class UnaryPredicate >
size_type remove_if(UnaryPredicate p);

void reverse();
size_type unique();

template< class BinaryPredicate >
size_type unique(BinaryPredicate p);

// void sort();
// void sort(Compare comp);



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
    const_iterator(const_iterator&& rhv) noexcept = default;
    ~const_iterator() = default;

//Assigments
public:
    const_iterator operator=(const const_iterator& other) = default;
    const_iterator operator=(const_iterator&& other) = default;


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
    ~iterator() = default;

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
    reverse_iterator& operator=(const reverse_iterator& rhv) = default;
    reverse_iterator& operator=(reverse_iterator&& other) = default;

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