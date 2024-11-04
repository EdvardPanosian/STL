#ifndef __LIST_TPP__
#define __LIST_TPP__
#include "List.hpp"


//Constructor
template<typename T>
List<T>::List():head(nullptr),tail(nullptr),List_size(0)
                    {}



template<typename T>
List<T>::List(value_type value) {
    
    Node* newNode = new Node(value);
    
    this->head = newNode;
    this->tail = newNode;

    this->head->next = nullptr;
    this->head->prev = nullptr;
}


template<typename T>
List<T>::List(const List& rhv):head(nullptr){

    if(rhv.head == nullptr){

        return;
    }

    Node* currentRhv = rhv.head;
    Node* currentThis = new Node(currentRhv->data);
    head = currentThis;

    while(currentRhv->next != nullptr){

        currentRhv = currentRhv->next;
        currentThis->next = new Node(currentRhv->data);
        currentThis = currentThis->next;
    }
}


template<typename T>
List<T>::List(List&& other){

    if(other.head != nullptr){

        this->head = other.head;
        this->tail = other.tail;
        this->List_size = other.List_size;

        other.head = nullptr;
        other.tail = nullptr;
        other.List_size = value_type{};
    }
        
}

template<typename T>
List<T>::List(std::initializer_list<T> init)
            :head(nullptr),tail(nullptr),List_size(0){

                for(const auto& val : init){

                    Node* newNode = new Node(value);
                    if(tail){
                        tail->next = newNode;
                    }
                    else{
                        head = newNode;
                    }

                    tail = newNode;
                    +++List_size;
                }
}


template<typename T>
List<T>::~List(){

    Node* current = head;
    while(current != nullptr){

        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }    
}


//Assigments
template<typename T>
List<T>& List<T>::operator=(const List& rhv){

    if(this->head != rhv.head){
        this->clear();

        if(rhv.head == nullptr){

            this->head = nullptr;
            this->tail = nullptr;
            this->List_size = 0;
            return *this;
        }

        this->head = new Node(rhv.head->data);
        this->head->prev = nullptr;
        Node* currentThis = this->head;
        Node* currentRhv = rhv.head->next;

        while(currentRhv != nullptr){

            Node* newNode = new Node(currentRhv->data);
            currentThis->next = newNode;
            newNode->prev = currentThis;
            currentThis = newNode;
            currenttRhv =currentRhv->next;
        }

        this->tail = currentThis;
        this->List_size = rhv->List_size;
    }

    return *this;    
}


template<typename T>
List<T>& List<T>::operator=(List&& rhv){

    if(this != &rhv){

        this->clear();

        this->head = rhv.head;
        this->tail = rhv.tail;
        this->List_size = rhv.List_size;

        rhv.head = nullptr;
        rhv.tail = nullptr;
        rhv.List_size = 0;
    }
}


//Element access
template<typename T>
typename List<T>::value_type List<T>::front() const{

    if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return this->head->data;
}

template<typename T>
typename List<T>::value_type List<T>::back() const{

    if(this->tail == nullptr){

        throw std::out_of_range("List s empty");
    }

    return this->tail->data;
}


//Iterators
template<typename T>
typename List<T>::iterator List<T>::begin(){

    if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return iterator(this->head);
}


template<typename T>
typename List<T>::const_iterator List<T>::begin() const{

    if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return const_iterator(this->head);
}

template<typename T>
typename List<T>::const_iterator List<T>::cbegin() const{

     if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return const_iterator(this->head);
}


template<typename T>
typename List<T>::iterator List<T>::end(){

    return iterator(nullptr);
}


template<typename T>
typename List<T>::const_iterator List<T>::end()const{

    return const_iterator(nullptr);
}


template<typename T>
typename List<T>::const_iterator List<T>::cend()const{

    return const_iterator(nullptr);
}


template<typename T>
typename List<T>::reverse_iterator List<T>::rbegin(){

    if(this->tail == nullptr){

        throw std::out_of_range("List is empty");
    }

    return reverse_iterator(this->tail);
}


template<typename T>
typename List<T>::const_reverse_iterator List<T>::rbegin() const{

    if(this->tail == nullptr){

        throw std::out_of_range("List is empty");
    }

    return const_reverse_iterator(this->tail);
}


template<typename T>
typename List<T>::const_reverse_iterator List<T>::crbegin() const{

    if(this->tail == nullptr){

        throw std::out_of_range("List is empty");
    }

    return const_reverse_iterator(this->tail);
}


template<typename T>
typename List<T>::reverse_iterator List<T>::rend(){

    return reverse_iterator(nullptr);
}


template<typename T>
typename List<T>::const_reverse_iterator List<T>::rend() const{

    return const_reverse_iterator(nullptr);
}


template<typename T>
typename List<T>::const_reverse_iterator List<T>::crend() const{

    return const_reverse_iterator(nullptr);
}


//Capacity
template<typename T>
bool List<T>::empty() const{

    return this->head == nullptr;
}


template<typename T>
typename List<T>::size_type List<T>::size() const{

    return this->List_size;
}


//Modifiers
template<typename T>
void List<T>::clear(){

    if(this->head != nullptr){

        Node* current = this->head;

        while(current != nullptr){

            Node* tmp = current;
            current = current->next;
            delete tmp;
        }

        this->head = nullptr;
        this->tail = nullptr;
        this->List_size = 0;
    }

}

template<typename T>
void List<T>::insert(const_reference value,const_reference pos){

    if(pos > this->List_size){

        throw std::out_of_range("Pos out of range");
    }

    Node* newNode = new Node(value);

    if(pos == 0){

        if(this->head  == nullptr){

            this->head = this->tail = nullptr;
        }

        else{

            newNode->next = this->head;
            this->head->prev = newNode;
            head = newNode;
        }
    }

    else if(pos == this->List_size){

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

        else{

            Node* current = head;
            for(size_type i = 0;i < pos;++i){

                current = current->next;
            }

            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }

        ++this->List_size;

}


template<typename T>
void List<T>::emplace(const_reference pos, const_reference value) {

    if (pos > this->List_size) {
        throw std::out_of_range("Position out of range");
    }

    Node* newNode = new Node(value);

    if (pos == 0) {
        if (this->head == nullptr) { 

            this->head = this->tail = newNode;
        } else {

            newNode->next = this->head;
            this->head->prev = newNode;
            this->head = newNode;
        }
    }

    else if (pos == List_size) {

        tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
    
    else {
        Node* current = head;
        for (size_type i = 0; i < pos; ++i) {

            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }

    ++List_size;
}


template<typename T>
void List<T>::erase(const_reference pos){

    if(pos > this->List_size){

        throw std::out_of_range("Pos out of range");
    }

    Node* DeleteNode = this->head;

    if(pos == 0){

        DeleteNode = this->head;

        this->head = this->head->next;
        if(head){

            this->head->prev = nullptr;
        }else{

            this->tail = nullptr;
        }
    }

    else if(pos == this->List_size - 1){

        DeleteNode = tail;
        tail = tail->prev;

        if(tail){

            this->tail->next = nullptr;;
        }else{

            this->head = nullptr;
        }
    }

    else{

        DeleteNode = head;
        for(size_type i = 0;i < pos;++i){

            DeleteNode = DeleteNode->next;
        }

        DeleteNode->prev->next = DeleteNode->next;
        DeleteNode->next->prev = DeleteNode->prev;
    }

    delete DeleteNode;

    --this->List_size;
}


template<typename T>
void List<T>::push_back(const_reference value){

    Node* NewNode = new Node(value);

    if(this->head == nullptr)
    {
        this->head = NewNode;
        this->tail = NewNode;
    }

    else{

    this->tail->next = NewNode;
    NewNode->prev = tail;
    tail = NewNode;
    }

    ++this->List_size;
}


template<typename T>
void List<T>::pop_back(){

    if(this->tail == nullptr){

        return;
    }

    if(this->head == this->tail){

        delete this->tail;
        this-head = this->tail = nullptr;
    }
    else{
    Node* DeleteNode = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = nullptr;
    delete DeleteNode;
    }
}

template<typename T>
void List<T>::push_front(const_reference value){

    Node* NewNode = new Node(value);

    if(this->head == nullptr){

        this->head = NewNode;
        this->tail = nullptr;
    }

    else{

        NewNode->next = this->head;
        this->head->prev = NewNode;
        this->head = NewNode;
    }

    ++this->List_size;
}

template<typename T>
void List<T>::pop_front(){

    if(this->head == nullptr){

        return;
    }

    if(this->head == this->tail){

        delete this->head;
        this->head = this->tail = nullptr;
    }
    else{

        Node* tmp = this->head;
        this->head = this->head->next;
        this->head->prev = nullptr;
        delete tmp;
    }

    --this->List_size;
}


template<typename T>
void List<T>::resize(const_reference new_size,const_reference value = value_type{}){

    while(new_size > this->List_size){

        push_back(value);
    }

    while(new_size < this->List_size){

        pop_back();
    }
}

template<typename T>
void List<T>::swap(const_reference value1, const_reference value2) {
    if (value1 == value2) {

        return;
    }

    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for (Node* current = this->head; current != nullptr; current = current->next) {
        
        if (current->data == value1) {
         
            node1 = current;
        } else if (current->data == value2) {
         
            node2 = current;
        }

        if (node1 && node2) {
         
            break;
        }
    }

    if (!node1 || !node2) {
        
        return;
    }

    if (node1->next == node2) {
        
        node1->next = node2->next;
        node2->prev = node1->prev;

        if (node1->prev) {
           
            node1->prev->next = node2;
        } else {
           
            this->head = node2;
        }

        if (node2->next) {
           
            node2->next->prev = node1;
        } else {
           
            this->tail = node1;
        }

        node2->next = node1;
        node1->prev = node2;
    } 
    else {
      
        Node* tempPrev = node1->prev;
        Node* tempNext = node1->next;

        if (node1->prev) {
      
            node1->prev->next = node2;
        } 
        else {
        
            this->head = node2;
        }

        if (node2->prev) {
        
            node2->prev->next = node1;
        }
         else {
        
            this->head = node1;
        }

        if (node1->next) {
        
            node1->next->prev = node2;
        }
         else {
        
            this->tail = node2;
        }

        if (node2->next) {
        
            node2->next->prev = node1;
        }
         else {
        
            this->tail = node1;
        }

        node2->next = tempNext;
        node1->next = node2->next;
        node1->prev = node2->prev;
        node2->prev = tempPrev;
    }
}


//Non-member function
template<typename T>
bool List<T>::operator==(const List& other) const{

    if(this->List_size != other.List_size){

        return false;
    }

    Node* thisCurrent = this->head;
    Node* otherCurrent = other.head;

    while(thisCurrent != nullptr && otherCurrent != nullptr){

        if(thisCurrent->data != otherCurrent.data){

            return false;
        }

        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    } 

    return thisCurrent == nullptr && otherCurrent == nullptr;
}


template<typename T>
bool List<T>::operator<(const List& other) const{

    Node* thisCurrent = this->head;
    Node* otherCurrent = other.head;

    while(thisCurrent != nullptr && otherCurrent != nullptr){

        if(thisCurrent->data > otherCurrent->data){

            return false;
        }

        if(thisCurrent->data < otherCurrent->data){

            return true;
        }

        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    }

    return thisCurrent == nullptr && otherCurrent != nullptr;
}

template<typename T>
bool List<T>::operator<=(const List& other) const{

    if(this->List_size < other.List_size){

        return true;
    }    

    if(this->List_size > other.List_size){

        return false;
    }

    Node* thisCurrent = this->head;
    Node* otherCurrent = other.head;

    while(thisCurrent != nullptr && otherCurrent.data){

        if(thisCurrent->data > otherCurrent.data){
            
            return false; 
        }
        if(thisCurrent->data < otherCurrent.data){

            return true;
        }

        thisCurrent = thisCurrent->next;
    }

    return thisCurrent == nullptr;
}



template<typename T>
bool List<T>::operator>(const List& other) const {

    Node* thisCurrent = this->head;
    Node* otherCurrent = other.head;

    while (thisCurrent != nullptr && otherCurrent != nullptr) {
    
        if (thisCurrent->data > otherCurrent->data) {
         
            return true;
        }

        if (thisCurrent->data < otherCurrent->data) {
        
            return false;
        }

        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    }

    return thisCurrent != nullptr;
}


template<typename T>
bool List<T>::operator>=(const List& other) const {

    Node* thisCurrent = this->head;
    Node* otherCurrent = other.head;

    while (thisCurrent != nullptr && otherCurrent != nullptr) {
    
        if (thisCurrent->data > otherCurrent->data) {
      
            return true;
        }
      
        if (thisCurrent->data < otherCurrent->data) {
      
            return false;
        }
      
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    }

    return thisCurrent != nullptr;
}


///////////////////////////////////////////////////////////////////////

//Class Const_Iterator

template<typename T>
List<T>::const_iterator::const_iterator(Node* node)
            :current(node)
                    {}


//Operators
template<typename T>
typename List<T>::const_reference
List<T>::const_iterator::operator*() const{

    return this->current->data;
}


template<typename T>
typename List<T>::const_pointer
List<T>::const_iterator::operator->() const{

    return &(this->current->data);
}

template<typename T>
List<T>::const_iterator& 
List<T>::const_iterator::operator++(){

    if(this->current){

        this->current = this->current->next;
    }

    return *this;
}


template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator++(int){

    const_iterator tmp = *this;
    if(this->current){

        this->current = this->current->next;
    }

    return tmp;
}


template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator+(const int n) const{

   const_iterator tmp = *this;

   for(int i = 0;i < n;++i){
    if(tmp.current){

        tmp.current = tmp.current->next;
    }
    else
    {
        break;
    }

   }

   return tmp;
}


template<typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator+=(int n){

    for(int i = 0;i < n;++i){

        if(this->current){

            this->current = this->current->next;
        }
        else{
            break;
        }
    }

    return *this;
}


template<typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator--(){

    if(this->current){

        this->current = this->current->prev;
    }

    return *this;
}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator--(int){

    const_iterator tmp = *this;

    if(this->current){

        this->current = this->current->prev;
    }    

    return tmp;
}


template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator-(const int n) const{

    const_iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current){

            tmp.current = tmp.current->prev;
        }
        else{

            break;
        }
    }

    return tmp;
}


template<typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator-=(const int n){

    if(this->current == nullptr){

        throw std::out_of_range("Error:Iterator out of range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->prev != nullptr){

            this->current = this->current->prev;
        }
        else{

            throw std::out_of_range("Error: Iterator out of range");
        }
    }

    return *this;
}

//Non-member function
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator& other) const{

    return this->current == other.current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& other) const{

    return !(this->current == other.current);    
}


////////////////////////////////////////////////////////////////////////////////

//Class Iterator

template<typename T>
List<T>::iterator::iterator(Node* node)
            :current(node)
                {}


//Operators
template<typename T>
typename List<T>::reference 
List<T>::iterator::operator*(){

    if(this->current == nullptr){

        throw std::out_of_range("Iterator is out of range");
    }

    return this->current->data;
}


template<typename T>
typename List<T>::const_reference
List<T>::iterator::operator*() const{

     if(this->current == nullptr){

        throw std::out_of_range("Iterator is out of range");
    }

    return this->current->data;
}


template<typename T>
typename List<T>::pointer
List<T>::iterator::operator->(){

    if(this->current == nullptr){

        throw std::out_of_range("Iterator is out of range");
    }

    return &(this->current);
}

template<typename T>
typename List<T>::const_pointer
List<T>::iterator::operator->() const{

     if(this->current == nullptr){

        throw std::out_of_range("Iterator is out of range");
    }

    return &(this->current);
}


template<typename T>
typename List<T>::iterator&
List<T>::iterator::operator++(){

    if(this->current == nullptr){

        throw std::out_of_range("Iterator out of range");
    }

    this->current = this->current->next;
    return *this;
}


template<typename T>
typename List<T>::iterator
List<T>::iterator::operator++(int){

    iterator tmp = *this;
    
    if(this->current == nullptr){

        throw std::out_of_range("Iterator out of range");
    }

    this->current = current->next;

    return tmp;
}

template<typename T>
typename List<T>::iterator
List<T>::iterator::operator+(const int n) const{

    iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current != nullptr){

            tmp.current = tmp.current->next;
        }
        else{

            break;
        }
    }
    return tmp;
}


template<typename T>
typename List<T>::iterator&
List<T>::iterator::operator+=(const int n){

    for(int i = 0;i < n;++i){

        if(this->current != nullptr){

            this->current = current->next;
        }
        else{

            break;
        }
    }

    return *this;
}


template<typename T>
typename List<T>::iterator&
List<T>::iterator::operator--(){

    if(this->current == nullptr){

        throw std::out_of_range("Iterator out of renge");
    }

    this->current = this->current->prev;
   
    return *this;
}


template<typename T>
typename List<T>::iterator
List<T>::iterator::operator--(int){

    iterator tmp = *this;

    if(this->current == nullptr){

        throw std::out_of_range("Error out of range");
    }

    if(this->current->prev != nullptr){
        
    this->current = this->current->prev;
    }

    else{

         throw std::out_of_range("Error out of range");
    }

    return tmp;
}


template<typename T>
typename List<T>::iterator
List<T>::iterator::operator-(const int n) const{

    if(this->current == nullptr){

        throw std::out_of_range("Error out of range")
    }

    iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current != nullptr){

            tmp.current = tmp.current->prev;
        }
        else{

           throw std::out_of_range("Error: Reached the beginning of the list");
        }
    }

    return tmp;
} 


template<typename T>
typename List<T>::iterator&
List<T>::iterator::operator-=(const int n){

    if(this->current == nullptr){

        throw std::out_of_range("Error iterator out of range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->prev != nullptr){

            this->current = this->current->prev;
        }
        else{

            throw std::out_of_range("Error iterator out of range")
        }
    }

    return *this;
}


//Non-member functions
template<typename T>
bool List<T>::iterator::operator==(const List& other) const{

    return this->current == other.current;
}


template<typename T>
bool List<T>::iterator::operator!=(const List& other) const{

    return !(*this == other);
}


//////////////////////////////////////////////////////////////////////////////

//Class Const Reverse Iterator

template<typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(Node* node)
                    :current(node)
                            {}



//Operators
template<typename T>
typename List<T>::const_reference
List<T>::const_reverse_iterator::operator*() const{

    if(this->current == nullptr){

        throw std::out_of_range("Error iterator out ot range");
    }

    return this->current->data;
}


template<typename T>
typename List<T>::const_pointer
List<T>::const_reverse_iterator::operator->() const{

    if(this->current == nullptr){

        throw std::out_of_range("Error iterator out ot range");
    }

    return &(this->current->data);
}


template<typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator++(){

    if(this->current == nullptr){

        throw std::out_of_range("Error iterator out ot range");
    }

    this->current = this->current->prev;

    return *this;
}


template<typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator++(int){

    if(this->current == nullptr){

        throw std::out_of_range("Error iterator out ot range");
    }

    const_reverse_iterator tmp = *this;
    this->current = this->current->prev;
    return tmp;
}


template<typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator+(const int n) const{

    if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }

    const_reverse_iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current->prev != nullptr){

            tmp.current = tmp.current->prev;
        }
        else{

             throw std::out_of_range("Error iterator out ot range");
        }
    }

    return tmp;
}


template<typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator+=(const int n){

    if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->prev != nullptr){

            this->current = this->current->prev;
        }
        else{

             throw std::out_of_range("Error iterator out ot range");
        }
    }

    return *this;
}


template<typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator--(){

    if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }


    this->current = this->current->next;
    return *this;
}


template<typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator--(int){

    if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }

    const_reverse_iterator tmp = *this;
    this->current = this->current->next;
    return tmp;

}


template<typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator-(const int n) const{

     if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }

    const_reverse_iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current->next != nullptr){

            tmp.current = tmp.current->next;
        }
        else{

            throw std::out_of_range("Error iterator out ot range");
        }
    }

    return tmp;
}


template<typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator-=(const int n){

     if(this->current == nullptr){

         throw std::out_of_range("Error iterator out ot range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->next != nullptr){

            this->current = this->current->next;
        }
        else{

            throw std::out_of_range("Error iterator out ot range");
        }
    }

    return *this;
}

//Non-member function
template<typename T>
bool List<T>::const_reverse_iterator
::operator==(const const_reverse_iterator& other) const{

    return this->current == other.current;
}


template<typename T>
bool List<T>::const_reverse_iterator
::operator!=(const const_reverse_iterator& other) const{

    return !(*this == other);
}


/////////////////////////////////////////////////////////////////////////////////


//Class Reverse Iterator

template<typename T>
List<T>::reverse_iterator::reverse_iterator(Node* node)
                        :current(node)
                            {}


//Operators
template<typename T>
typename List<T>::reference
List<T>::reverse_iterator::operator*(){

    if (this->current == nullptr) {
        throw std::out_of_range("Error: Iterator is out of range");
    }

    return this->current->data;
}

template<typename T>
typename List<T>::const_reference
List<T>::reverse_iterator::operator*() const{

    if (this->current == nullptr) {
        throw std::out_of_range("Error: Iterator is out of range");
    }

    return this->current->data;

}

template<typename T>
typename List<T>::pointer
List<T>::reverse_iterator::operator->(){

    if (this->current == nullptr) {
        throw std::out_of_range("Error: Iterator is out of range");
    }

    return &(this->current->data);
}


template<typename T>
typename List<T>::const_pointer
List<T>::reverse_iterator::operator->() const{

    if (this->current == nullptr) {
        throw std::out_of_range("Error: Iterator is out of range");
    }

    return &(this->current->data);
}


template<typename T>
typename List<T>::reverse_iterator&
List<T>::reverse_iterator::operator++(){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    this->current = this->current->prev;
    return *this;
}


template<typename T>
typename List<T>::reverse_iterator
List<T>::reverse_iterator::operator++(int){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    reverse_iterator tmp = *this;
    this->current = this->current->prev;
    return tmp;
}


template<typename T>
typename List<T>::reverse_iterator
List<T>::reverse_iterator::operator+(const int n) const{

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    reverse_iterator tmp = *this;
    for(int i = 0;i < n;++i){

        if(tmp.current->prev != nullptr){

            tmp.current = tmp.current->prev;
        }
        else{

            throw std::out_of_range("Error Iterator is out of range");
        }
    }

    return tmp;
}


template<typename T>
typename List<T>::reverse_iterator&
List<T>::reverse_iterator::operator+=(const int n){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->prev != nullptr){

            this->current = this->current->prev;
        }
        else{

            throw std::out_of_range("Error Iterator is out of range");
        }
    }

    return *this;
}


template<typename T>
typename List<T>::reverse_iterator&
List<T>::reverse_iterator::operator--(){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    this->current = this->current->next;
    return *this;
}


template<typename T>
typename List<T>::reverse_iterator
List<T>::reverse_iterator::operator--(int){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    reverse_iterator tmp = *this;
    this->current = this->current->next;
    return tmp;
}


template<typename T>
typename List<T>::reverse_iterator
List<T>::reverse_iterator::operator-(const int n) const{

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    reverse_iterator tmp = *this;

    for(int i = 0;i < n;++i){

        if(tmp.current->next != nullptr){

            tmp.current = tmp.current->next;
        }
        else{

            throw std::out_of_range("Error Iterator is out of range");
        }
    }

    return tmp;
} 


template<typename T>
typename List<T>::reverse_iterator&
List<T>::reverse_iterator::operator-=(const int n){

    if(this->current == nullptr){

        throw std::out_of_range("Error Iterator is out of range");
    }

    for(int i = 0;i < n;++i){

        if(this->current->next != nullptr){

            this->current = this->current->next;
        }
        else{

            throw std::out_of_range("Error Iterator is out of range");
        }
    }

    return *this;
}


//Non-member functions
template<typename T>
bool List<T>::reverse_iterator
::operator==(const reverse_iterator& other) const{

    return this->current == other.current;
}


template<typename T>
bool List<T>::reverse_iterator
::operator!=(const reverse_iterator& other) const{

    return !(*this == other);
}

#endif