#include <iostream>
#include <stdexcept>
#include "Queue.hpp"  

void testQueue() {

    Queue<int> q1;
    

    q1.empty() == true;
    q1.size() == 0;


    q1.push(10);
    q1.push(20);
    q1.push(30);


    q1.empty() == false;
    q1.size() == 3;
    q1.front() == 10;

    
    q1.pop();
    q1.size() == 2;
    q1.front() == 20;

    q1.pop();
    q1.size() == 1;
    q1.front() == 30;

    
    q1.pop();
    q1.empty() == true;
    q1.size() == 0;

    
    Queue<int> q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);
    q1 != q2; 

    Queue<int> q3;
    q3.push(10);
    q3.push(20);
    q3.push(30);
    q2 == q3; 

    std::cout << "All tests passed!" << std::endl;
}

int main() {

    testQueue();
    return 0;
}
