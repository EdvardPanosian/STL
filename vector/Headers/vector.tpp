#include "vector.hpp"


namespace {
//Ctors
template <typename T>
Vector<T>::Vector()
   : v_arr(nullptr)
   ,v_size(0)
   ,v_capacity(0)
   {}

template <typename T>
Vector<T>::Vector(const Vector& rhv){
    this -> v_size = rhv.v_size;
    this -> v_capacity = rhv.v_capacity;
    this -> v_arr = new value_type[rhv.v_capacity];

    for(int i = 0;i < rhv.v_size;++i)
    {
        this -> v_arr[i] = rhv.v_arr[i];
    }
}   

template <typename T>
Vector<T>::Vector(Vector&& rhv){
    this -> v_size = rhv.v_size;
    this -> v_capacity = rhv.v_capacity;
    this -> v_arr = rhv.v_arr;

    rhv.v_size = 0;
    rhv.v_capacity = 0;
    rhv.v_arr = nullptr;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init):Vector(){
    for(const_reference val : init)
    {
        push_back(val);
    }
}

template <typename T>
Vector<T>::Vector(size_type count,const_reference val):v_size(count),v_capacity(count){
    
    v_arr = new value_type[v_capacity];

    for(int i = 0;i < count;++i)
    {
       v_arr[i] = val;
    }
}

template <typename T>
Vector<T>::~Vector(){
    clear();
}

//Assigment
template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector& rhv){
    if(this != &rhv)
    {
      this-> clear();

      this -> v_size = rhv.v_size;
      this -> v_capacity = rhv.v_capacity;
      this -> v_arr = new value_type[rhv.v_capacity];

      for(int i = 0;i < rhv.v_capacity;++i)
      {
        this -> arr[i] = rhv.arr[i];
      }
    }

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& rhv){
    if(this != &rhv){
        
        this->clear();

        this -> v_size = rhv.v_size;
        this -> v_capacity = rhv.v_capacity;
        this -> v_arr = rhv.v_arr;

        rhv.v_size = 0;
        rhv.v_capacity = 0;
        rhv.v_arr = nullptr;
    }
    return *this;
}


//Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos){
    if(pos >= this -> v_size){
        throw std::out_of_range("Error");
    }

    return v_arr[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const{
    if(pos >= v_size){
        throw std::out_of_range("Error");
    }

    return v_arr[pos]; 
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos){
    return v_arr[pos];
} 

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const{
    return v_arr[pos];
}

template <typename T>
Vector<T>::reference Vector<T>::front(){
    if(this -> v_size  == 0){
        throw std::out_of_range("Error");
    }

    return this -> v_arr[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const{
    if(this -> v_size  == 0){
        throw std::out_of_range();
    }

    return this -> v_arr[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back(){
    if(this -> v_size == 0){
        throw std::out_of_range("Out of the range");
    }

    return this -> v_arr[v_size - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const{
    if(this -> v_size == 0){
        throw std::out_of_range("Error");
    }

    return this -> v_arr[v_size - 1]; 
}



//Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin(){

   return iterator(v_arr);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const{
    
    return const_iterator(v_arr); 
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const{

    const_iterator it = v_arr;
    return it;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end(){

    return iterator(v_arr  + v_size);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const{

    return const_iterator(v_arr + v_size);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const{

    return const_iterator(v_arr + v_size);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin(){

    return reverse_iterator(v_arr + v_size - 1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const{

    return const_reverse_iterator(v_arr + v_size -1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const{

    return const_reverse_iterator(v_arr + v_size - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend(){

    return reverse_iterator(v_arr - 1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const{

    return const_reverse_iterator(v_arr - 1);
} 

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const{

    return const_reverse_iterator(v_arr - 1);
} 

//Capacity
template <typename T>
bool Vector<T>::empty() const{
    if(v_size == 0)
    {
        return true;
    }

    return false;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::Size() const{

    return this -> v_size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::Capacity() const{

    return this -> v_capacity;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap){

    if(new_cap > v_capacity){
        pointer new_arr = new value_type[new_cap];

        for(int i = 0;i < v_capacity;++i){
            new_arr[i] = v_arr[i];
        }
       
        delete [] v_arr;
        v_arr = new_arr;
        v_capacity = new_cap;
    }
}


//Modifiers
template <typename T>
void Vector<T>::clear(){

    delete [] v_arr;
    v_arr = nullptr;
    v_size = 0;
    v_capacity = 0;
}

template <typename T>
typename Vector<T>::iterator 
Vector<T>::insert(const_iterator pos, const_reference value){

    if(v_size + 1 > v_capacity){
        
      reserve(2 * v_capacity);
    }

    size_type index = pos.ptr - v_arr;

    for(int i = v_size;i >= index;--i){

        v_arr[i] = v_arr[i - 1];
    }    

    v_arr[index] = value;

    return iterator(&v_arr[index]);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::insert(const_iterator pos, size_type count, const_reference value){
   
    size_type index = pos - v_arr;
     
    if(count == 0){

        return begin();
    } 

    if(v_size + count > v_capacity){
    
        reserve(v_capacity + count);
    }

    for(int i = v_size - 1;i != index;--i){
    
        v_arr[count + i] = v_arr[i];
    }
    
    for(int i = 0;i < count;++i){

        v_arr[index + i] = value;
    } 
    
    v_size = v_size + count;

    return (begin() + index);
}

template <typename T>
typename Vector<T>::iterator 
Vector<T>::insert(const_iterator pos, std::initializer_list<value_type> init) {
    auto index = pos - this->begin();  
    for (const auto& elem : init) {
        this->insert(this->begin() + index, elem);
        ++index;
    }
    return this->begin() + index - init.size();  
    
    }


 template <typename T>
template <typename InputIt>
typename Vector<T>::const_iterator 
Vector<T>::insert(const_iterator pos, InputIt first, InputIt last) {
   
    auto index = pos - this->begin();  
    
    for (auto it = first; it != last; ++it) {

        this->insert(this->begin() + index, *it);  
                ++index;
    }
    return this->begin() + index - (last - first);
}


 template <typename T>
 typename Vector<T>::iterator Vector<T>::erase(const_iterator pos){

    size_type index = pos - v_arr;
    if(index < v_size){
        for(int i = index;i < v_size - 1;++i){
            v_arr[i] = v_arr[i + 1];
        }

        v_size--;

     return begin() + index;
    }
 }

 template <typename T>
 typename Vector<T>::iterator 
 Vector<T>::erase(const_iterator first, const_iterator last){
     
    auto mid = last - first;
    size_type index = first - v_arr;
    
    for(int i = index;i < last;++i){

        v_arr[i] = v_arr[i + mid];
    }

    v_size -= mid;

    return begin() + index;;
 }


 template <typename T>
 void Vector<T>::push_back(const_reference val){

    if(v_size == v_capacity || v_size == 0){
    
        reserve(v_capacity + 1);
    }

    v_arr[v_size] = val;
 }


template <typename T>
void Vector<T>::pop_back(){

    if(v_size != 0){

      v_size--;
    }
}

template <typename T>
void Vector<T>::resize(size_type new_size,const_reference val){

  if(new_size != v_size){
    
    if(new_size > v_capacity){

        reserve(new_size);
        for(int i = v_size; i < new_size;++i){

            v_arr[i] = val;
        }

        v_size = new_size;
    }

    else{
        if(new_size > v_size){

            for(int i = v_size; i < new_size;++i){

                v_arr[i] = val;
          }

          v_size = new_size;
        }

        else{
            for(int i = new_size;i < v_size;++i){

                v_arr[i] = 0;
            }

            v_size = v_size - (v_size - new_size); 
        }
    }
  }

}


//Non-member functions
template <typename T>
bool Vector<T>::operator==(const Vector& other) const{

    if(this -> v_size != other.Size()){
        
        return false;
    }

    for(int i = 0;i < v_size;++i){

        if(this -> v_arr[i] != other.v_arr[i]){

            return false;
        }
    }

    return true;
}


template <typename T>
bool Vector<T>::operator!=(const Vector& other) const{

    return !(*this == other);
}


template <typename T>
bool Vector<T>::operator<(const Vector& other) const{

    size_type min_size = std::min(this -> v_size,other.Size());
    for(int i = 0;i < min_size;++i){

        if(this -> v_arr[i] < other[i]){

            return true;
        }

        if(this -> v_arr[i] > other[i]){

            return true;
        }
    }

   return this -> v_size < other.Size();
}

template <typename T>
bool Vector<T>::operator>(const Vector& other) const{

    return other < *this;
}


template <typename T>
bool Vector<T>::operator<=(const Vector& other) const{

    return !(other < *this);
}


template <typename T>
bool Vector<T>::operator>=(const Vector& other) const{

    return !(*this < other);
}


template <typename T>
int Vector<T>::compare(const Vector& other) const{

    if(*this > other){
        
        return 1;
    }

    if(*this == other){

        return 0;
    }

    if(*this < other){

        return -1;
    }
}


//////////////////////////////////////////////////////////////////////////

//Class const_iterator
template <typename T>
Vector<T>::const_iterator::const_iterator(pointer ptr)
   :ptr{ptr}
    { }


//Operators
template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator+(size_type count) const{

    return const_iterator(ptr + count);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator-(size_type count) const{

    return const_reference (ptr - count);
}

template <typename T>
typename Vector<T>::const_reference 
Vector<T>::const_iterator::operator[](size_type index){

    return ptr[index];
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_iterator::operator*() const{

    return *ptr;
}

template <typename T>
typename Vector<T>::const_pointer
Vector<T>::const_iterator::operator->() const{

    return ptr;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator++(){

    ++ptr;
    return *this;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator++(int){

    const_iterator tmp = *this;
    ++ptr;

    return tmp;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator--(){

    --ptr;
    return *this;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator--(int){

    const_iterator tmp = *this;
    --ptr;
    return tmp;
}


//Non-member functions
template <typename T>
bool Vector<T>::const_iterator::operator==(const const_iterator& other) const{

    return ptr == other.ptr;
}

template <typename T>
bool Vector<T>::const_iterator::operator!=(const const_iterator& other) const{

    return ptr != other.ptr; 
}

template <typename T>
bool Vector<T>::const_iterator::operator>(const const_iterator& other) const{

    return ptr > other.ptr;
}

template <typename T>
bool Vector<T>::const_iterator::operator>=(const const_iterator& other) const{

    return ptr >= other.ptr;
}

template <typename T>
bool Vector<T>::const_iterator::operator<(const const_iterator& other) const{

    return ptr < other.ptr;
}

template <typename T>
bool Vector<T>::const_iterator::operator<=(const const_iterator& other) const{

    return ptr <= other.ptr;
}


//////////////////////////////////////////////////////////////////////////////////

//Class Iterator

template <typename T>
Vector<T>::iterator::iterator(pointer ptr) 
    :const_iterator(ptr)
    {}

//OPerators
template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator+(size_type count) const{

   return iterator(this->ptr + count);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator-(size_type count) const{

   return iterator(this -> ptr - count);   
}

template <typename T>
int Vector<T>::iterator::operator-(const const_iterator& other) const{

    if(this > other.ptr){

      return static_cast<value_type>(this->ptr - other.ptr);
    }
}

template <typename T>
typename Vector<T>::reference 
Vector<T>::iterator::operator[](size_type index){

    return this -> ptr[index];
}


template <typename T>
typename Vector<T>::reference
Vector<T>::iterator::operator*(){

    return *this -> ptr;
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::iterator::operator->(){

    return &(this -> ptr);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator++(){

     ++this;
     return this;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator++(int){

    iterator tmp = *this;
    ++this -> ptr;
    return tmp;
}


////////////////////////////////////////////////////////////////////////

//Class Const_reverse_iterator
template <typename T>
Vector<T>::const_reverse_iterator::
const_reverse_iterator(pointer ptr)
            :ptr{ptr}
            {}


template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator+(size_type count){

    return const_reverse_iterator(this -> ptr - count);
}            

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator-(size_type count) {

    return const_reverse_iterator(this -> ptr + count);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator++(){

   --(this -> ptr);
 
   return *this;
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator++(int){

    const_reverse_iterator tmp = *this;
    --(this -> ptr);

    return tmp;
}


template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator--(){

    ++(this -> ptr);

    return *this;
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator--(int){

    const_reverse_iterator tmp = *this;
    ++(this -> ptr);

    return tmp;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator*() const{

    return*(this -> ptr);
}

template <typename T>
typename Vector<T>::const_pointer
Vector<T>::const_reverse_iterator::operator->() const{

    return ptr;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator[](size_type index){

    return *(ptr - index);
}


//Non-member functions
template <typename T>
bool Vector<T>::const_reverse_iterator
::operator==(const const_reverse_iterator& other) const{

  return this->ptr == other.ptr;
}

template <typename T>
bool Vector<T>::const_reverse_iterator
::operator!=(const const_reverse_iterator& other) const{

    return this->ptr != other.ptr;
}

template <typename T>
bool Vector<T>::const_reverse_iterator
::operator>(const const_reverse_iterator& other) const{

    return this->ptr < other.ptr;
}

template <typename T>
bool Vector<T>::const_reverse_iterator
::operator>=(const const_reverse_iterator& other) const{

    return this->ptr >= other.ptr;
}

template <typename T>
bool Vector<T>::const_reverse_iterator
::operator<(const const_reverse_iterator& other) const{

    return this->ptr < other.ptr;
}

template <typename T>
bool Vector<T>::const_reverse_iterator
::operator<=(const const_reverse_iterator& other) const{

    return this->ptr <= other.ptr;
}


///////////////////////////////////////////////////////////////

//Class Revers_iterator

template  <typename T>
Vector<T>::reverse_iterator::reverse_iterator(pointer ptr)
                     :const_reverse_iterator(ptr)
                     {}



//Operators
template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator+(size_type count) {

    return reverse_iterator(v_arr - count);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator-(size_type count) {

    return reverse_iterator(this->ptr + count);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator++(){

    --this->ptr;
    return *this;
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator++(int){

    reverse_iterator tmp = *this;
    --this->ptr;
    return *tmp;
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator--(){

    ++this->ptr;
    return *this;
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator--(int){
    
    reverse_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator*(){

    return *this->ptr;
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::reverse_iterator::operator->(){

    return this->ptr;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator[](size_type index){

    return this->ptr[index];
}

}