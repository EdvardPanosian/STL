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

                    Node* newNode = new Node(val);
                    if(tail){
                        tail->next = newNode;
                    }
                    else{
                        head = newNode;
                    }

                    tail = newNode;
                    ++List_size;
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
            currentRhv =currentRhv->next;
        }

        this->tail = currentThis;
        this->List_size = rhv.List_size;
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
typename List<T>::reference List<T>::front(){

    if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return this->head->data;
}

template<typename T>
typename List<T>::const_reference List<T>::front() const{

    if(this->head == nullptr){

        throw std::out_of_range("List is empty");
    }

    return this->head->data;
}



template<typename T>
typename List<T>::reference List<T>::back(){

    if(this->tail == nullptr){

        throw std::out_of_range("List s empty");
    }

    return this->tail->data;
}


template<typename T>
typename List<T>::const_reference List<T>::back() const{

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
typename List<T>::const_iterator List<T>::cbegin() const noexcept{

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
typename List<T>::const_iterator List<T>::end() const{

    return const_iterator(nullptr);
}


template<typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept{

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
typename List<T>::const_reverse_iterator List<T>::crbegin() const noexcept{

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
typename List<T>::const_reverse_iterator List<T>::crend() const noexcept{

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
List<T>::iterator
List<T>::insert(const_iterator pos,const_reference value){

    Node* newNode = new Node(value);
    Node* posNode = pos.current;

    if(posNode == nullptr){

        if(this->tail == nullptr){

            this->head = this->tail = newNode;
        }
        else{

            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = newNode;
        }
    }

    else{

        newNode->next = posNode;
        newNode->prev = posNode->prev;

        if(posNode->prev){

            posNode->prev->next = newNode;
        }
        else{

            this->head = newNode;
        }

        posNode->prev = newNode;
    }

    ++this->List_size;
    return iterator(newNode);        
}


template<typename T>
typename List<T>::iterator
List<T>::insert(const_iterator pos,value_type&& value){

    Node* newNode = new Node(std::move(value));
    Node* posNode = pos.current;

    if(pos == nullptr){

        if(this->tail == nullptr){

            this->head = this->tail = newNode;
        }
        else{

            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = newNode; 
        }
    }
    else{

        newNode->next = posNode;
        newNode->prev = posNode->prev;

        if(posNode->prev != nullptr){

            posNode->prev->next = newNode;
        }
        else{

            this->head = newNode;
        }

    posNode->prev = newNode;
    }

    ++this->List_size;
    return iterator(newNode);
}


template<typename T>
typename List<T>::iterator
List<T>::insert(const_iterator pos,size_type count,const_reference value){

    if(count == 0){

        return iterator(pos.current);
    }

    iterator StartNewList = insert(pos,value);
    iterator EndNewList = StartNewList;

    for(int i = 0;i < count;++i){

        EndNewList = insert(EndNewList,value);
    }

    this->List_size += count;
    return StartNewList;
}


template<typename T>
typename List<T>::iterator
List<T>::insert(const_iterator pos,std::initializer_list<value_type> init){

    if(init.size() == 0){

        return iterator(pos.current);
    }

    iterator result = const_cast<iterator>(pos);    
    for(const auto& item : init){

        result = insert(result,item);
        ++result;
    }

    this->List_size += init.size();
    return const_cast<iterator>(pos);
}


template<typename T>
template<typename InputIt>
typename List<T>::iterator
List<T>::insert(const_iterator pos,InputIt first,InputIt last){
    
    iterator result = const_cast<iterator>(pos);
    iterator FirstInsert = result;

    if(first == last){

        return result;
    }

    FirstInsert = insert(result,*first);
    ++first;

    for(;first != last;++first){

        insert(result,*first);
    }

    return FirstInsert;     
}


template<typename T>
typename List<T>::iterator
List<T>::erase(const_iterator pos){

   Node* DeleteNode = pos.current;
   Node* NextNode = DeleteNode->next;
   Node* PrevNode = DeleteNode->prev;

   if(PrevNode != nullptr){

    PrevNode->next = NextNode;
   }
   else{

    this->head = NextNode;
   }

   if(NextNode != nullptr){

    NextNode->prev = PrevNode;
   }
   else{

    this->tail = PrevNode; 
   }

   delete DeleteNode;
   --this->List_size;

   return List<T>::iterator(NextNode),this->end();
}


template<typename T>
typename List<T>::iterator 
List<T>::erase(const_iterator first,const_iterator last){

    iterator it = first;
    
    while (it != last){
    
        it = erase(it); 
    }
    
    return it;
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
void List<T>::push_back(value_type&& value){

    Node* NewNode = new Node(std::move(value));

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
        this->head = this->tail = nullptr;
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
void List<T>::push_front(value_type&& value){

    Node* NewNode = new Node(std::move(value));

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
void List<T>::resize(size_type new_size){

     if(new_size > this->List_size){

        while(new_size >this->List_size){

            push_back(T());
        }
    }
    else if(new_size < this->List_size){

        while(new_size < this->List_size){

            pop_back();
        }
    }
}


template<typename T>
void List<T>::resize(size_type new_size,const_reference value){

    if(new_size > this->List_size){

        while(new_size >this->List_size){

            push_back(value);
        }
    }
    else if(new_size < this->List_size){

        while(new_size < this->List_size){

            pop_back();
        }
    }
}


template<typename T>
void List<T>::swap(List& other){
    
    if(*this != other){
        
    std::swap(this->head,other.head);
    std::swap(this->tail,other.tail);
    std::swap(this->head,other.head);
    }
}


//Operations
template<typename T>
void List<T>::merge(List& other){

    if(this == &other){

        return;
    }

    auto thisIt = this->begin();
    auto otherIt = other.begin();

    while(thisIt != this->end() && otherIt != other.end()){

        if(*otherIt < *thisIt){

            insert(thisIt,std::move(*otherIt));
            otherIt = other.erase(otherIt);
        }
        else{

            ++thisIt;
        }
    }

    splice(this->end(),other);
}


template<typename T>
void List<T>::merge(List&& other){

    if(this == &other){

        return;
    }

    auto thisIt = this->begin();
    auto otherIt = other.begin();

    while(thisIt != this->end() && otherIt != other.end()){

        if(*otherIt < *thisIt){

            insert(thisIt,std::move(*otherIt));
            otherIt = other.erase(otherIt);
        }
        else{
            
            ++thisIt;
        }
    }

    splice(this->end(),other);
}


template<typename T>
template<typename Compare>
void List<T>::merge(List& other,Compare comp){

    if(this == &other){

        return;
    }

    auto thisIt = this->begin();
    auto otherIt = other.begin();

    while(thisIt != this->end() && otherIt != other.end()){

        if(comp(otherIt,thisIt)){

            insert(thisIt,std::move(*otherIt));
            otherIt = other.erase(otherIt);
        }
        else{
            
            ++thisIt;
        }
    }

    splice(this->end(),other);
}


template<typename T>
template<typename Compare>
void List<T>::merge(List&& other,Compare){

    if(this == &other){

        return;
    }

    auto thisIt = this->begin();
    auto otherIt = other.begin();

    while(thisIt != this->end() && otherIt != other.end()){

        if(comp(otherIt,thisIt)){

            insert(thisIt,std::move(*otherIt));
            otherIt = other.erase(otherIt);
        }
        else{
            
            ++thisIt;
        }
    }

    splice(this->end(),other);
}


template<typename T>
void List<T>::splice(const_iterator pos,List& other){

    if(this == &other || other.empty()){

        return;
    }

    if(pos.current->prev){

        pos.current->prev->next = other.head;
    }

    if(other.tail){

        other.tail->next = pos.current;
    }

    if(pos == this->begin){

        this->head = other.head;
    }

    if(pos == this->end()){

        this->tail = other.tail;
    }

    other.head = nullptr;
    other.tail = nullptr;
}


template<typename T>
void List<T>::splice(const_iterator pos,List&& other){

    splice(pos,other);
}


template<typename T>
void List<T>::splice(const_iterator pos,List& other, const_iterator it){

    if(other.empty() || this = &other){

        return;
    }

    Node* targetNode = it.current;

    if(targetNode == other.head){

        other.head = targetNode->next;
    }
    else{

        Node* prev = other.head;
        while(prev && prev->next != targetNode){

            prev = prev->next;
        }
        if(prev != nullptr){

            prev->next = targetNode->next;
        }
        else{

            Node* temp = this->head;
            while(temp && temp->next != pos.current){

                temp = temp->next;
            }

            if(temp != nullptr){

                targetNode->next = temp->next;
                temp->next = targetNode;
            }
        }
    }
}


template<typename T>
 void List<T>::splice(const_iterator pos, List&& other, const_iterator it) {
        if (!it.current || !other.head){
            
            return;
        }

        Node* targetNode = it.current;
        if (targetNode == other.head) {
         
            other.head = targetNode->next;
        }
         else {
        
            Node* prev = other.head;
            while (prev && prev->next != targetNode) {
        
                prev = prev->next;
        
            }
            if (prev) {
        
                prev->next = targetNode->next;
            }
        }

        
        if (pos.current == head) {
        
            targetNode->next = head;
            head = targetNode;
        }
        else {
        
            Node* temp = head;
            while (temp && temp->next != pos.current) {
        
                temp = temp->next;
            }
            if (temp) {
        
                targetNode->next = temp->next;
                temp->next = targetNode;
            }
        }
    }


template<typename T>
void List<T>::splice(const_iterator pos, List& other, const_iterator first, const_iterator last) {
       
        if (first == last || !other.head){
         
             return;
        }
        
        Node* rangeStart = first.current;
        Node* rangeEnd = first.current;
        Node* prev = nullptr;

            while (rangeEnd && rangeEnd != last.current) {

            prev = rangeEnd;
            rangeEnd = rangeEnd->next;
        }

        if (rangeStart == other.head) {

            other.head = rangeEnd;
        }
         else if (prev) {
        
            prev->next = rangeEnd;
        }

        
        if (pos.current == head) {
        
            Node* temp = rangeStart;
            while (temp->next != rangeEnd) {
        
                temp = temp->next;
            }
        
            temp->next = head;
            head = rangeStart;
        }
        else {
        
            Node* temp = head;
            while (temp && temp->next != pos.current) {
        
                temp = temp->next;
            }
            if (temp) {
        
                Node* endNode = rangeStart;
                while (endNode->next != rangeEnd) {
        
                    endNode = endNode->next;
                }
        
                endNode->next = temp->next;
                temp->next = rangeStart;
            }
        }
    }


template<typename T>
void List<T>::splice(const_iterator pos, List&& other, const_iterator first, const_iterator last) {
    
    if (first == last || !other.head) return;

    
    Node* rangeStart = first.current;
    Node* rangeEnd = rangeStart;
    Node* prev = nullptr;


    while (rangeEnd && rangeEnd != last.current) {

        prev = rangeEnd;
        rangeEnd = rangeEnd->next;
    }


    if (rangeStart == other.head) {

        other.head = rangeEnd;
    }
    else if (prev) {
           
            prev->next = rangeEnd;
    }

    if (pos.current == head) {

        Node* temp = rangeStart;
        while (temp->next != rangeEnd) {
    
            temp = temp->next;
            }
    
            temp->next = head;
            head = rangeStart;
        } 
        else {
        
            Node* temp = head;
            while (temp && temp->next != pos.current) {
        
                temp = temp->next;
            }
            if (temp) {
        
                Node* endNode = rangeStart;
                while (endNode->next != rangeEnd) {
        
                    endNode = endNode->next;
                }
        
                endNode->next = temp->next;
                temp->next = rangeStart;
        }
    }
}


template<typename T>
List<T>::size_type List<T>::remove(const_reference value){

    size_type removed_count = 0;
    Node* current = this->head;
    Node* prev = nullptr;

    while(current != nullptr){

        if(current->data == value){

            if(prev){

                prev->next = current->next;
            }
            else{

                this->head = current->next;
            }

            Node* tmp = current;
            current = current->next;
            delete tmp;
            ++removed_count;
        }
        else{

            prev = current;
            current = current->next;
        }
    }
    return removed_count;
}


template<typename T>
template<typename UnaryPredicate>
List<T>::size_type List<T>::remove_if(UnaryPredicate p){

    size_type removed_count = 0;
    Node* current = this->head;
    Node* prev = nullptr;

    while(current != nullptr){

        if(p(current->data)){

            if(prev){

                prev->next = current->next;
            }
            else{

                this->head = current->next;
            }

            Node* tmp = current;
            current = current->next;
            delete tmp;
            ++removed_count;
        }
        else{

            prev = current;
            current = current->next;
        }
    }
    return removed_count;
}


template <typename T>
void List<T>::reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current) {
        next = current->next;  
        current->next = prev;  
        prev = current;        
        current = next;        
    }

    head = prev;
}


template<typename T>
List<T>::size_type List<T>::unique(){

    if(this->List_size < 2){

        return 0;
    }

    size_type delete_count = 0;
    Node* current = this->head;

    while(current != nullptr && current->next != nullptr){

        if(current->data = current->next->data){

            Node* DeleteNode = current->next;
            current->next = DeleteNode->next;
            if(DeleteNode->next != nullptr){

                DeleteNode->next->prev = current;
            }
            else{

                 this->tail = current;
            }

            delete DeleteNode;
            delete_count++;
            --this->List_size; 
        }
        else{

            current = current->next;
        }
    }

    return delete_count;
}


template<typename T>
template< class BinaryPredicate >
List<T>::size_type List<T>::unique(BinaryPredicate p){

    if(this->List_size < 2){

        return 0;
    }

    size_type delete_count = 0;
    Node* current = this->head;

    while(current != nullptr && current->next != nullptr){

        if(p(current->data,current->next->data)){

            Node* DeleteNode = current->next;
            current->next = DeleteNode->next;
            if(DeleteNode->next != nullptr){

                DeleteNode->next->prev = current;
            }
            else{

                this->tail = current;
            }

            delete DeleteNode;
            this->List_size--;
            ++delete_count;
        }
        else{

            current = current->next;
        }
    }

    return delete_count;
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
bool List<T>::operator!=(const List& other) const{

    return!(*this == other);
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

        throw std::out_of_range("Error out of range");
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

            throw std::out_of_range("Error iterator out of range");
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