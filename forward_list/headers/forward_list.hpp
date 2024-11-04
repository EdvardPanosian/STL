#ifndef __Forward_List__
#define __Forward_List__

#include <iostream>
#include <initializer_list>
#include <iterator>


template <typename T>
class forward_list{

private:
    class Node{
    private:
        T data;
        Node* next;

        //Node Ctor 
        Node(const_reference value):data(value),next(nullptr)
            {}

      friend class forward_list;
      friend class iterator;
      friend class const_iterator;     
    };


Node* head;        

//Member types
public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using rvalue_reference = value_type&&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const pointer;

//Iterators
public:
    class iterator;
    class const_iterator;


//Constructors and Destuctor
public:
    forward_list();
    forward_list(const forward_list& rhv);
    forward_list(forward_list&& other); 
    forward_list(std::initializer_list<T> init);   
    ~forward_list();

//Member functions
public:
    forward_list& operator=(const forward_list& rhv);
    forward_list& operator=(forward_list&& rhv);

    
//Elemet access
public:
    const value_type front() const;


//Iterators
public:
    iterator befor_begin();
    const_iterator before_begin() const;
    const_iterator cbefore_begin() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;     


//Capacity
public:
    bool empty() const;


//Modifiers
public:
    void clear();
    void insert_after(Node* new_Node,const_reference val);
    void emplace_after(Node* new_Node,const_reference val);
    
    template<typename Iterator>
    void insert_range_after(Node* prevNode,Iterator start,Iterator end);
    void erase_after(Node* prevNode);
    void push_front(const_reference val);
    void push_front(rvalue_reference val);
    void pop_front();
    void resize(size_type new_size,const_reference val = {});
    void swap(forward_list& other);


//Operations
public:
    void splice_after(Node* pos,forward_list& other);
    void reverse();
    void unique();


//Non-member functions
public:
    bool operator==(const forward_list& rhv) const;
    bool operator!=(const forward_list& rhv) const;
    bool operator>(const forward_list& rhv) const;
    bool operator>=(const forward_list& rhv) const;
    bool operator<(const forward_list& rhv) const;
    bool operator<=(const forward_list& rhv) const;

};

///////////////////////////////////////////////////////////////////////////

//Class Const_iterator

template<typename T>
class forward_list<T>::const_iterator{

private:
    forward_list<T>::Node* current;

//Constructor
public:
    const_iterator() = default;
    explicit const_iterator(Node* node);
    const_iterator(const const_iterator& other) = default;
    const_iterator(const iterator& other) = delete;
    const_iterator(const_iterator&& other) = default;

//Assigmets
public:
    const const_iterator operator=(const const_iterator& rhv) = default;
    const const_iterator operator=(const iterator rhv) = default;


//Operators
public:
    const reference operator*() const;
    const pointer operator->() const;

    const_iterator& operator++();
    const_iterator operator++(int);


//Non-member functions
public:
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;


};

////////////////////////////////////////////////////////////////

//Class Iterator

template<typename T>
class forward_list<T>::iterator{

private:
    forward_list<T>::Node* current;

public:    
    //Constructor
    iterator() = default;
    iterator(Node* node);
    iterator(const iterator& other) = default;
    iterator(iterator&& other) = default;


//Assigments
public:
     iterator& operator=(const iterator& rhv) = default;
     iterator& operator=(iterator&& rhv) noexcept = default;

//Operators
public:
    reference operator*();
    const_reference operator*() const;

    pointer operator->();
    const_pointer operator->() const;

    iterator& operator++();
    iterator operator++(int);


//Non-member functions
public:
    bool operator==(const forward_list& other);
    bool operator!=(const forward_list& other);

};

#include "fordward_list.tpp"
#endif