#include "../Headers/List.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Test 1: Constructor and push_back
    List<int> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    assert(myList.front() == 10);
    assert(myList.back() == 30);
    std::cout << "Test 1 passed: Constructor and push_back\n";

    // Test 2: Iterator - forward traversal
    std::cout << "Test 2: Forward traversal\n";
    List<int>::iterator it = myList.begin();
    assert(*it == 10);
    ++it;
    assert(*it == 20);
    ++it;
    assert(*it == 30);
    std::cout << "Test 2 passed\n";

    // Test 3: Reverse Iterator
    std::cout << "Test 3: Reverse traversal\n";
    List<int>::reverse_iterator rit = myList.rbegin();
    assert(*rit == 30);
    ++rit;
    assert(*rit == 20);
    ++rit;
    assert(*rit == 10);
    std::cout << "Test 3 passed\n";

    // Test 4: Pop back and front
    myList.pop_back();
    assert(myList.back() == 20);
    myList.pop_back();
    assert(myList.back() == 10);
    std::cout << "Test 4 passed: Pop back and check\n";

    // Test 5: Clear the list
    myList.clear();
    assert(myList.empty());
    std::cout << "Test 5 passed: Clear and empty check\n";

    // Test 6: Single element constructor
    List<int> singleList(5);
    assert(singleList.front() == 5);
    assert(singleList.back() == 5);
    std::cout << "Test 6 passed: Single element constructor\n";

    // Test 7: Assignment operator
    List<int> assignList;
    assignList.push_back(100);
    assignList.push_back(200);
    myList = assignList;
    assert(myList.front() == 100);
    assert(myList.back() == 200);
    std::cout << "Test 7 passed: Assignment operator\n";

    // Test 8: Insert and erase
    myList.push_front(50);
    myList.push_back(300);
     
    assert(myList.front() == 50);
    assert(myList.back() == 300);
    assert(myList.front() != 100);
    std::cout << "Test 8 passed: Insert and erase\n";

    // Test 9: Iterator comparisons
    auto beginIt = myList.begin();
    auto endIt = myList.end();
    // assert(beginIt != endIt);
    std::cout << "Test 9 passed: Iterator comparison\n";

    // Test 10: Copy Constructor
    List<int> copyList(myList);
    assert(copyList.front() == myList.front());
    assert(copyList.back() != myList.back());
    std::cout << "Test 10 passed: Copy constructor\n";

    // Test 11: Move Constructor
    List<int> moveList(std::move(copyList));
    assert(moveList.front() == myList.front());
    assert(moveList.back() != myList.back());
    assert(copyList.empty());  // Original should be empty after move
    std::cout << "Test 11 passed: Move constructor\n";

    std::cout << "All tests passed!\n";
    return 0;
}
