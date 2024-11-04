#ifndef __Vector__H__
#define __Vector__H__

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

namespace  {

template <typename T>
class Vector{

//Member types
public:
   using value_type = T;
   using size_type = std::size_t;
   using reference = value_type&;
   using const_reference = const value_type&;
   using pointer = value_type*;
   using const_pointer = const value_type*;


//Iterator class 
public:
   class iterator;
   class const_iterator;
   class reverse_iterator;
   class const_reverse_iterator;


//Constructors
public:
   Vector();
   Vector(const Vector& rhv);
   Vector(Vector&& rhv);
   Vector(std::initializer_list<T> init);
   Vector(size_type count,const_reference val = value_type{});
   ~Vector();


//Assigments
public:
  const Vector& operator = (const Vector& rhv);
  Vector& operator = (Vector&& rhv);


//Element access
public:
  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const; 


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
  size_type Size() const;
  size_type Capacity() const;
  void reserve(size_type new_cap);


//Modifiers
public:  
  void clear();
  
  iterator insert(const_iterator pos, const_reference value);
  iterator insert(const_iterator pos, size_type count, const_reference value);
  iterator insert(const_iterator pos, std::initializer_list<value_type> init);

  template <typename InputIt>
  const_iterator insert(const_iterator pos, InputIt first, InputIt last);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  void push_back(const_reference val);
  void pop_back();
  void resize(size_type new_size, const_reference val);


//Non-member functions
public:
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;
  bool operator>(const Vector& other) const;
  bool operator>=(const Vector& other) const;
  bool operator<(const Vector& other) const;
  bool operator<=(const Vector& other) const;


private:
  int compare(const Vector& other) const;


///Members
private:
  size_type v_size;
  size_type v_capacity;
  pointer v_arr;  
};

/////////////////////////////////////////////////////////////////////////////////////////////////////


//Class const_iterator
template <typename T>
class Vector<T>::const_iterator{

  friend class Vector<T>;

protected:
  pointer ptr; 


//Ctor const_iterator
private:
  const_iterator(pointer ptr);

public:
  const_iterator() = default;
  const_iterator(const const_iterator& it) = default;
  const_iterator(const iterator& it) noexcept = default;


//Assigment 
public:
  const_iterator& operator=(const const_iterator& other) = default;
  const_iterator& operator=(const_iterator&& other) = default;


//Operators
public:
  const_iterator operator+(size_type count) const;
  const_iterator operator-(size_type count) const;

  const_reference operator[](size_type index);
  
  const_reference operator*() const;
  const_pointer operator->() const;
  
  const_iterator operator++();
  const_iterator operator++(int);
  const_iterator operator--();
  const_iterator operator--(int); 


//Non-member functions
public:
  bool operator==(const const_iterator& other) const;
  bool operator!=(const const_iterator& other) const;
  bool operator>(const const_iterator& other) const;
  bool operator>=(const const_iterator& other) const;
  bool operator<(const const_iterator& other) const;
  bool operator<=(const const_iterator& other) const;

};



///////////////////////////////////////////////////////////////////////////////////////////////

//Class Iterator
template <typename T>
class Vector<T>::iterator : public Vector<T>::const_iterator{

  friend class Vector<T>;

//Ctor
public:
  iterator() = default;
  explicit iterator(pointer ptr);
  iterator(const iterator& other) = default;
  iterator(iterator&& other) = default;


//Assigment
public:
  iterator& operator=(const iterator& other) = default;
  iterator& operator=(iterator&& other) = default;


//Operators
public:
  iterator operator+(size_type count) const;
  iterator operator-(size_type count) const;
  int operator-(const const_iterator& other) const;

  reference operator[](size_type index);

  reference operator*();
  pointer operator->();

  iterator operator++();
  iterator operator++(int);
  iterator operator--();
  iterator operator--(int);

};


////////////////////////////////////////////////////////////////////////////////////////////////////

//Class Const_reverce_iterator
template <typename T>
class Vector<T>::const_reverse_iterator{

  friend class Vector<T>;

private:
  pointer ptr;

protected:
  const_reverse_iterator(pointer ptr);

//Ctor
public:
  const_reverse_iterator() = default;
  const_reverse_iterator(const const_reverse_iterator& other) = default;
  const_reverse_iterator(const_reverse_iterator&& other) = default;


//Assigment
public:
  const const_reverse_iterator operator=(const const_reverse_iterator& other) = default;
  const const_reverse_iterator operator=(const reverse_iterator& other) noexcept = default;


//Operators
public:
  const_reverse_iterator operator+(size_type count);
  const_reverse_iterator operator-(size_type count);

  const_reverse_iterator operator++();
  const_reverse_iterator operator++(int);
  const_reverse_iterator operator--();
  const_reverse_iterator operator--(int);

  const_reference operator*() const;
  const_pointer operator->() const;

  const_reference operator[](size_type index);


//Non-member functions
public:
  bool operator==(const const_reverse_iterator& other) const;
  bool operator!=(const const_reverse_iterator& other) const;
  bool operator>(const const_reverse_iterator& other) const;
  bool operator>=(const const_reverse_iterator& other) const;
  bool operator<(const const_reverse_iterator& other) const;
  bool operator<=(const const_reverse_iterator& other) const;

};


///////////////////////////////////////////////////////////////////////////////////////////////////


//Class Reverse_iterator

template<typename T>
class Vector<T>::reverse_iterator:public Vector<T>::const_reverse_iterator{

friend class Vector<T>;

private:
  reverse_iterator(pointer ptr);


//Ctor
public:
  reverse_iterator() = default;
  reverse_iterator(const reverse_iterator& other) = default;
  reverse_iterator(reverse_iterator&& other) = default;


//Assigment
public:
  const reverse_iterator operator=(const reverse_iterator& other) = default;
  const reverse_iterator operator=(reverse_iterator&& other) = default; 


//Operators
public:
  reverse_iterator operator+(size_type count);
  reverse_iterator operator-(size_type count);

  reverse_iterator operator++();
  reverse_iterator operator++(int);
  reverse_iterator operator--();
  reverse_iterator operator--(int);

  reference operator*();
  pointer operator->();

  reference operator[](size_type index);

};

}

#include "vector.tpp"
#endif