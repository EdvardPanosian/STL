#include "../headers/forward_list.hpp"
#include <iostream>

int main(){

    forward_list<int> fl ={ 2,3,4};
    forward_list<int> fl2 = {2,4,5};


    fl.push_front(55);

    auto it = fl.begin();

    std::cout << *it << std::endl; 

    return 0; 
}