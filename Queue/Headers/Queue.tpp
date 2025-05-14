#ifndef __Queue__
#define __Queue_TPP__
#include "Queue.hpp"

//Constructors
template <typename T>
Queue<T>::Queue() = default;

template <typename T>
Queue<T>::Queue(size_type count, const_reference value) 
            : data (count, value)
                    {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) 
            : data (other.data)
                    {}

template <typename T>
Queue<T>::Queue(Queue<T>&& other) 
            : data (std::move(other.data))
                    {}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> init)
            : data (init) 
                    {}

template <typename T>
Queue<T>::~Queue() {};
            

//Member functions
template <typename T>
Queue<T>& 
Queue<T>::operator= (const Queue<T>& rhv) {

    if (this != &rhv) {
    
        this->data = rhv.data;    
    }
}

template <typename T>
Queue<T>&
Queue<T>::operator= (Queue<T>&& rhv) {

     if (this != &rhv) {
    
        this->data = std::move(rhv.data);    
    }
}


//Element access
template <typename T>
typename Queue<T>::reference
Queue<T>::front() {

    if (this->data.empty()) {

        throw std::out_of_range("Queue is empty");
    }

    return this->data.front();
}


template <typename T>
typename Queue<T>::const_reference
Queue<T>::front() const {

    if (this->data.empty()) {

        throw std::out_of_range("Queue is empty");
    }

    return this->data.front();
}


template <typename T>
typename Queue<T>::reference
Queue<T>::back() {

    if (this->data.empty()) {

        throw std::out_of_range("Queue is empty");
    }

    return this->data.back();
}


template <typename T>
typename Queue<T>::const_reference
Queue<T>::back() const {

    if (this->data.empty()) {

        throw std::out_of_range("Queue is empty");
    }

    return this->data.back();
}


//Capacity
template <typename T>
bool Queue<T>::empty() const {

    return this->data.empty();
}


template <typename T>
typename Queue<T>::size_type
Queue<T>::size() const {

    return this->data.size();
}


//Modifiers
template <typename T>
void Queue<T>::push(Queue<T>::const_reference value) {

    this->data.push_back(value);
}


template <typename T>
void Queue<T>::push(Queue<T>::rvalue_reference value) {

    this->data.push_back(std::move(value));
}


template <typename T>
void Queue<T>::pop() {

    if (this->data.empty()) {

        throw std::out_of_range("Queue is empty");
    }

    this->data.erase(this->data.begin());
}


template <typename T>
void swap(Queue<T>& other) noexcept {

    this->data.swap(other.data);
}


//Non-member functions
template <typename T>
bool Queue<T>::operator==(const Queue<T>& rhv) const {

    return this->data == rhv.data;
}


template <typename T>
bool Queue<T>::operator!=(const Queue<T>& rhv) const {

    return this->data != rhv.data;
}

template <typename T>
bool Queue<T>::operator<(const Queue<T>& rhv) const {

    return this->data < rhv.data;
}

template <typename T>
bool Queue<T>::operator<=(const Queue<T>& rhv) const {

    return this->data <= rhv.data;
}

template <typename T>
bool Queue<T>::operator>(const Queue<T>& rhv) const {

    return this->data > rhv.data;
}

template <typename T>
bool Queue<T>::operator>=(const Queue<T>& rhv) const {

    return this->data >= rhv.data;
}

#endif