#ifndef __FORWARD_LIST_TPP__
#define __FORWARD_LIST_TPP__
#include "forward_list.hpp"

//Constructors

template<typename T>
forward_list<T>::forward_list():head(nullptr)
            {}


template<typename T>
forward_list<T>::forward_list(const forward_list& rhv):head(nullptr){

    if(rhv.head == nullptr){
        
        return;
    }

    this->head = new Node(rhv.head->data);
    Node* current = this->head;
    Node* rhv_current = rhv.head->next;

    while (rhv_current != nullptr) {
        current->next = new Node(rhv_current->data);
        current = current->next;
        rhv_current = rhv_current->next;
    }
}


template<typename T>
forward_list<T>::forward_list(forward_list&& other){

    this->head = other.head;
    other.head =nullptr;    
}


template<typename T>
forward_list<T>::forward_list(std::initializer_list<T> init){

    this->head = nullptr;
    Node** current = &(this->head);

    for(const T& value : init){

        *current = new Node(value);
        current = &((*current)->next);    
    }
}


template<typename T>
forward_list<T>::~forward_list(){

    clear();
}

//Member function
template<typename T>
forward_list<T>&
forward_list<T>::operator=(const forward_list& rhv){

    if(this != &rhv){

        this->clear();

        if(rhv.head == nullptr){

            this->head = nullptr;
            return *this;
        }

        this->head = new Node(rhv.head->data);
        Node* current = head;
        Node* rhv_current = rhv.head->next;

        while(rhv_current != nullptr){

            current->next = new Node(rhv_current->data);
            current = current->next;
            rhv_current = rhv_current->next;
        }
    }

    return *this;
}


template<typename T>
forward_list<T>& forward_list<T>::operator=(forward_list&& rhv){

    if(this != &rhv){

        this->clear();

        this->head = rhv.head;
        rhv.head = nullptr;
    }

    return *this;
}


//Element access
template<typename T>
const forward_list<T>::value_type
forward_list<T>::front() const{

    if(empty()){

        throw;
    }

    return head->data; 
}

//Iterators
template<typename T>
typename forward_list<T>::iterator forward_list<T>::befor_begin(){

    return forward_list<T>::iterator(nullptr);
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::before_begin() const{

    return forward_list<T>::const_iterator(nullptr);
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::cbefore_begin() const{

    return forward_list<T>::const_iterator(nullptr);
}

template<typename T>
typename forward_list<T>::iterator
forward_list<T>::begin(){

    return forward_list<T>::iterator(head);    
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::begin() const{

    return forward_list<T>::const_iterator(head);
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::cbegin() const{

    return forward_list<T>::const_iterator(head);
}

template<typename T>
typename forward_list<T>::iterator
forward_list<T>::end(){

    return forward_list<T>::iterator(nullptr);
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::end() const{

    return forward_list<T>::const_iterator(nullptr);
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::cend() const{

    return forward_list<T>::const_iterator(nullptr);
}

//Caapacity
template<typename T>
bool forward_list<T>::empty() const{

    return this->head == nullptr;
}

//Modifiers
template<typename T>
void forward_list<T>::clear(){

    Node* current = this->head;
    
    while(current != nullptr){

        Node* Del = current->next;
        delete current;
        current = Del;
    }

    this->head = nullptr;
}


template<typename T>
void forward_list<T>::insert_after(Node* new_Node,const_reference val){

    if(new_Node == nullptr){

        throw std::out_of_range("Error");
    }

    Node* new_node = new Node(val);

    new_node->next = new_Node->next;
    new_Node->next = new_node; 
}

template<typename T>
void forward_list<T>::emplace_after(Node* new_Node,const_reference val){

    if (new_Node == nullptr) {
        throw;
    }

    Node* new_node = new Node(val); 

    new_node->next = head->next; 
    head->next = new_node;
}

template<typename T>
template<typename Iterator>
void forward_list<T>::insert_range_after
(Node* prevNode,Iterator start,Iterator end){

    if(prevNode == nullptr){

        throw std::out_of_range("Error");
    }

    Node* current = prevNode;

    while(start != end){

        Node* new_node = new Node(*start);
        current->next = new_node;
        current = new_node;
        ++start;
    }
}

template<typename T>
void forward_list<T>::erase_after(Node* prevNode){

    if(prevNode == nullptr || prevNode->next == nullptr){

        return;
    }

    Node* node_Delete = prevNode->Next;
    prevNode->Next = node_Delete->next;

    delete node_Delete;
}

template<typename T>
void forward_list<T>::push_front(rvalue_reference val){

    Node* new_Node = new Node(val);
    new_Node->next = head;
    head = new_Node;
    
}

template<typename T>
void forward_list<T>::pop_front(){
    if(this->head != nullptr){

        Node* new_Node = this->head;
        this->head = this->head->next;
        delete new_Node;
    }    
}

template<typename T>
void forward_list<T>::resize(size_type new_size,const_reference val){

    size_type count = 0;
    Node* new_Node = this->head;

    while(new_Node != nullptr){

        ++count;
        new_Node = new_Node->next;
    }

    if(count != new_size){

        if(count < new_size){

            if(this->head == nullptr){

                this->head = new Node(val);
                new_Node = this->head;
                count++;
            }

            else{

                new_Node = this->head;
                while(new_Node->next != nullptr){

                    new_Node = new_Node->next;
                }
            }

            for(size_t i = count;i < new_size;++i){

                new_Node->next = new Node(val);
                new_Node = new_Node->next;
            }
        }
        

        else{
            
            new_Node = this->head;

            for(size_type i = 0;i < new_size - 1;++i){

                new_Node = new_Node->next;
            }

            Node* tmp = new_Node->next;
            new_Node->next = nullptr;

            while(tmp != nullptr){

                Node* Delete_Node = tmp;
                tmp = tmp->next;
                delete Delete_Node;
            }
        }
    }
}


template<typename T>
void forward_list<T>::swap(forward_list& other){

    Node* tmp = this->head;
    this->head = other.head;
    other.head = tmp;
}

//Operators
template<typename T>
void forward_list<T>::splice_after(Node* pos,forward_list& other){

    if(!pos || other.head == nullptr){

        return;
    }

    Node* other_tail = other.head;
    while(other_tail->next != nullptr){

        other_tail = other_tail->next;
    }

    other_tail->next = pos->next;
    pos->next = other.head;

    other.head = nullptr;
}

template<typename T>
void forward_list<T>::reverse(){

    Node* prev = nullptr;
    Node* current = this->head;
    Node* next = nullptr;

    while(current != nullptr){

        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    this->head = prev;
}

template<typename T>
void forward_list<T>::unique(){

    if(this->head == nullptr){

        return;
    }

    Node* current = this->head;

    while(current->next != nullptr){
        if(current->data = current->next->data){
            
            Node* duplicate = current->next;
            current->next = duplicate->next;
            delete duplicate;
        }

        else{
            current = current->next;
        }
    }

}

//Non-member function
template<typename T>
bool forward_list<T>::operator==(const forward_list& rhv) const{

    Node* current1 = head;
    Node* current2 = rhv.head;

    while(current1 != nullptr && current2 != nullptr){

        if(current1->data != current2->data){
            return false;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 == nullptr && current2 == nullptr;
}

template<typename T>
bool forward_list<T>::operator!=(const forward_list& rhv) const{

    return !(*this == rhv);
}

template<typename T>
bool forward_list<T>::operator>(const forward_list& rhv) const {
    
    Node* current1 = this->head;
    Node* current2 = rhv.head;

    while(current1 != nullptr && current2 != nullptr){
        
        if(current1->data > current2->data) {

            return true; 
        }
        
         else if(current1->data < current2->data){

            return false;
        }

        current1 = current1->next; 
        current2 = current2->next; 
    }

    return current1 != nullptr;
}

template<typename T>
bool forward_list<T>::operator>=(const forward_list& rhv) const{

    Node* current1 = nullptr;
    Node* current2 = nullptr;

    while(current1 != nullptr && current2 != nullptr){

        if(current1->data > current2->data){

            return true;
        }

        else if(current1->data < current2->data){

            return false;            
        }
    
    current1 = current1->next;
    current2 = current2->next;
    }

    return current1 != nullptr;
}

template<typename T>
bool forward_list<T>::operator<(const forward_list& rhv) const{

    Node* current1 = nullptr;
    Node* current2 = nullptr;

    while(current1 != nullptr && current2 != nullptr){

        if(current1->data < current2->data){

            return true;
        }

        else if(current1->data > current2->data){

            return false;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 != nullptr && current2 != nullptr;
}

template<typename T>
bool forward_list<T>::operator<=(const forward_list& rhv) const{

    Node* current1 = nullptr;
    Node* current2 = nullptr;

    while(current1 != nullptr && current2 != nullptr){

        if(current1->data < current2->data){

            return true;
        }

        else if(current1->data > current2->data){

            return false;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 == nullptr;
}

////////////////////////////////////////////////////////////////////////

//Class Const_iterator

template<typename T>
forward_list<T>::const_iterator::const_iterator(Node* node)
                    :current(node)
                    {}


//Assigments
template<typename T>
const forward_list<T>::reference
forward_list<T>::const_iterator::operator*() const{

    if(current == nullptr){

        return std::out_of_range("Error");
    }    

    return current->data;
}

template<typename T>
const forward_list<T>::pointer
forward_list<T>::const_iterator::operator->() const{

    if(current == nullptr){

        throw std::out_of_range();
    }

    return &(current->data);
}

template<typename T>
typename forward_list<T>::const_iterator&
forward_list<T>::const_iterator::operator++(){

    if(current != nullptr){

        current = current->next;
    }

    return *current;
}

template<typename T>
typename forward_list<T>::const_iterator
forward_list<T>::const_iterator::operator++(int){

    const_iterator tmp = *this;
    if(current != nullptr){

        current = current->next;
    }
    return tmp;
}

//Non-member functions
template<typename T>
bool forward_list<T>::const_iterator::operator==(const const_iterator& other) const{

    return this->current == other.current;
}


template<typename T>
bool forward_list<T>::const_iterator::operator!=(const const_iterator& other) const{

    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////

//Class Iterator

template<typename T>
forward_list<T>::iterator::iterator(Node* node)
            :current(node)
            {}

//Operators
template<typename T>
typename forward_list<T>::reference
forward_list<T>::iterator::operator*(){

    if(current == nullptr){

        throw std::out_of_range("Error");
    }

    return current->data;
}

template<typename T>
typename forward_list<T>::const_reference
forward_list<T>::iterator::operator*() const{

    if(current == nullptr){

        throw std::out_of_range("Error");
    }

    return current->data;
}

template<typename T>
typename forward_list<T>::pointer
forward_list<T>::iterator::operator->(){

    if(current == nullptr){

        throw std::out_of_range("Error");
    }

    return &(current->data);
}

template<typename T>
typename forward_list<T>::const_pointer
forward_list<T>::iterator::operator->() const{

    if(current == nullptr){

        throw std::out_of_range("Error");
    }

    return &(current->data);
}

template<typename T>
typename forward_list<T>::iterator&
forward_list<T>::iterator::operator++(){

    if(current != nullptr){

        current = current->next;
    }

    return *this;
}

template<typename T>
typename forward_list<T>::iterator
forward_list<T>::iterator::operator++(int){

    iterator tmp = *this;
    ++(*this);
    return tmp;
}

//Non-member function
template<typename T>
bool forward_list<T>::iterator::operator==(const forward_list& other){

    return this->head == other.head;
}

template<typename T>
bool forward_list<T>::iterator::operator!=(const forward_list& other){

    return this->head != other.head;
}


#endif