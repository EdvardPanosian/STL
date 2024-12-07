#ifndef __ARRAY__TPP__
#define __ARRAY__TPP__
#include "array.hpp"

//Constrctor
template<typename T,std::size_t N>
constexpr Array<T,N>::Array(std::initializer_list<T> init){

    size_type i = 0;

    for(const auto& elem : init){

        if(i < N){

            arr[i] = elem;
            ++i;
        }
    }
}


//Element access
template<typename T,std::size_t N>
constexpr typename Array<T,N>::reference
Array<T,N>::at(size_type pos){

    if(pos >= N){

        throw std::out_of_range("Index out of range");
    }

    return arr[pos];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::const_reference
Array<T,N>::at(size_type pos) const{

    if(pos >= N){

        throw std::out_of_range("Index out of range");
    }

    return arr[pos];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::reference
Array<T,N>::operator[](size_type pos){

    return arr[pos];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::const_reference
Array<T,N>::operator[](size_t pos) const{

    return arr[pos];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::reference
Array<T,N>::front(){

    if (N == 0) {
    
        throw std::out_of_range("Array is empty");
    }

    return arr[0];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::const_reference
Array<T,N>::front() const{

    if (N == 0) {
    
        throw std::out_of_range("Array is empty");
    }

    return arr[0];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::reference
Array<T,N>::back(){

    if (N == 0) {
    
        throw std::out_of_range("Array is empty");
    }

    return arr[N - 1];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::const_reference
Array<T,N>::back() const{

    if (N == 0) {
    
        throw std::out_of_range("Array is empty");
    }

    return arr[N - 1];
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::pointer  
Array<T,N>::data() noexcept{

    return arr;
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::const_pointer
Array<T,N>::data() const noexcept{

    return arr;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::begin() noexcept{

    return iterator(arr);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::begin() const noexcept{

    return const_iterator(arr);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::cbegin() const noexcept{

    return const_iterator(arr);
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::end() noexcept{

    return iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::end() const noexcept{

    return const_iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::cend() const noexcept{

    return const_iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::rbegin() noexcept{

    return reverse_iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::rbegin() const noexcept{

    return const_reverse_iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::crbegin() const noexcept{

    return const_reverse_iterator(arr + N);
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::rend() noexcept{

    return reverse_iterator(arr);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::rend() const noexcept{

    return const_reverse_iterator(arr);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::crend() const noexcept{

    return const_reverse_iterator(arr);
}


//Capacity
template<typename T,std::size_t N>
constexpr bool Array<T,N>::empty() const noexcept{

    return N == 0;
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::size_type
Array<T,N>::size() const noexcept{

    return N;
}


template<typename T,std::size_t N>
constexpr typename Array<T,N>::size_type 
Array<T,N>::max_size() const noexcept{

    return N;
}


//Operators
template<typename T,std::size_t N>
constexpr void Array<T,N>::fill(const_reference value){

    for(int i = 0;i < N;++i){

        arr[i] = value;
    }
}


template<typename T,std::size_t N>
constexpr void Array<T,N>::swap(Array& other) noexcept{

    for(int i = 0;i < N;++i){

        std::swap(arr[i],other.arr[i]);
    }
}


//Non-member fuctions
template<typename T,std::size_t N>
constexpr bool Array<T,N>::operator==(const Array<T,N>& rhv) const{

    for(int i = 0;i < N;++i){

        if(arr[i] != rhv.arr[i]){

            return false;
        }
    }

    return true;
}



///////////////////////////////////////////////////////////////////////////////////

//Class Const Iterator
template<typename T,std::size_t N>
Array<T,N>::const_iterator::
const_iterator(const_pointer p)
            :ptr{p}
            {}


//Operators
template<typename T,std::size_t N>
typename Array<T,N>::const_reference
Array<T,N>::const_iterator::operator*() const{

    return *ptr;
} 


template<typename T,std::size_t N>
typename Array<T,N>::const_pointer
Array<T,N>::const_iterator::operator->() const{

    return ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator&
Array<T,N>::const_iterator::operator++(){

    ++this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::const_iterator::operator++(int){

    const_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::const_iterator::operator+(const size_type n) const{

    return const_iterator(ptr + n);
} 


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator&
Array<T,N>::const_iterator::operator--(){

    --this->arr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::const_iterator::operator--(int){

    const_iterator tmp = *this;
    ++this->ptr;
    return tmp;;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::const_iterator::operator-(const size_type n) const{

    return const_iterator(ptr - n);
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator==(const const_iterator& other) const{

    return this->ptr == other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator!=(const const_iterator& other) const{

    return this->ptr != other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator<(const const_iterator& other) const{

    return this->ptr < other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator<=(const const_iterator& other) const{

    return this->ptr <= other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator>(const const_iterator& other) const{

    return this->ptr > other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_iterator::
operator>=(const const_iterator& other) const{

    return this->ptr >= other.ptr;
}


/////////////////////////////////////////////////////////////////////

//Class Iterator
template<typename T,std::size_t N>
constexpr Array<T,N>::iterator::
iterator(const pointer p)
        :ptr{p}
          {}


//Operators
template<typename T,std::size_t N>
typename Array<T,N>::reference
Array<T,N>::iterator::operator*() const{

    return *ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::pointer
Array<T,N>::iterator::operator->() const{

    return this->ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator&
Array<T,N>::iterator::operator++(){

    ++this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::iterator::operator++(int)
{

    iterator tmp = *this;
    ++this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::iterator::operator+(const size_type n) const{

    return iterator(ptr + n);
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator&
Array<T,N>::iterator::operator--(){

    --this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::iterator::operator--(int){

    iterator tmp = *this;
    --this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::iterator
Array<T,N>::iterator::operator-(const size_type n) const{

    return iterator(ptr - n);
}


template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator==(const iterator& other) const{

    return this->ptr == other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator!=(const iterator& other) const{

    return this->ptr != other.ptr;
}



template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator>(const iterator& other) const{

    return this->ptr > other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator>=(const iterator& other) const{

    return this->ptr >= other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator<(const iterator& other) const{

    return this->ptr < other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::iterator::
operator<=(const iterator& other) const{

    return this->ptr <= other.ptr;
}



/////////////////////////////////////////////////////////////////////////////

//Class Const Reverse Iterator

template<typename T,std::size_t N>
constexpr Array<T,N>::const_reverse_iterator::
const_reverse_iterator(const pointer p)
                :ptr{p}
                  {}


//Operators
template<typename T,std::size_t N>
typename Array<T,N>::const_reference
Array<T,N>::const_reverse_iterator::operator*() const{

    return *ptr;
}

template<typename T,std::size_t N>
typename Array<T,N>::const_pointer
Array<T,N>::const_reverse_iterator::operator->() const{

    return ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator&
Array<T,N>::const_reverse_iterator::operator++(){

    --this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::const_reverse_iterator::operator++(int){

    const_reverse_iterator tmp = *this;
    --this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::const_reverse_iterator::operator+(const size_type n) const{

    return const_reverse_iterator(ptr - n);
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator&
Array<T,N>::const_reverse_iterator::operator--(){

    ++this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::const_reverse_iterator::operator--(int){

    const_reverse_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::const_reverse_iterator
Array<T,N>::const_reverse_iterator::operator-(const size_type n) const{

    return const_reverse_iterator(ptr - n);
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator==(const const_reverse_iterator& other) const{

    return this->ptr == other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator!=(const const_reverse_iterator& other) const{

    return this->ptr != other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator>(const const_reverse_iterator& other) const{

    return this->ptr > other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator>=(const const_reverse_iterator& other) const{

    return this->ptr >= other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator<(const const_reverse_iterator& other) const{

    return this->ptr == other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::const_reverse_iterator::
operator<=(const const_reverse_iterator& other) const{

    return this->ptr == other.ptr;
}



///////////////////////////////////////////////////////////////////////////////

//Class Reverse Iterator

template<typename T,std::size_t N>
constexpr Array<T,N>::reverse_iterator::
reverse_iterator(const pointer p)
            :ptr{p}
                {}


//Operators
template<typename T,std::size_t N>
typename Array<T,N>::reference
Array<T,N>::reverse_iterator::operator*() const{

    return *ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::pointer 
Array<T,N>::reverse_iterator::operator->() const{

    return ptr;
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator&
Array<T,N>::reverse_iterator::operator++(){

    --this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::reverse_iterator::operator++(int){

    reverse_iterator tmp = *this;
    --this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::reverse_iterator::operator+(const size_type n) const{

    return reverse_iterator(ptr - n);
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator&
Array<T,N>::reverse_iterator::operator--(){

    ++this->ptr;
    return *this;
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::reverse_iterator::operator--(int){

    reverse_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}


template<typename T,std::size_t N>
typename Array<T,N>::reverse_iterator
Array<T,N>::reverse_iterator::operator-(const size_type n) const{

    return reverse_iterator(ptr - n);
}


//Non-member function
template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator==(const reverse_iterator& other) const{

    return this->ptr == other.ptr;
}

template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator!=(const reverse_iterator& other) const{

    return this->ptr != other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator>(const reverse_iterator& other) const{

    return this->ptr > other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator>=(const reverse_iterator& other) const{

    return this->ptr >= other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator<(const reverse_iterator& other) const{

    return this->ptr < other.ptr;
}


template<typename T,std::size_t N>
bool Array<T,N>::reverse_iterator::
operator<=(const reverse_iterator& other) const{

    return this->ptr <= other.ptr;
}

 
#endif