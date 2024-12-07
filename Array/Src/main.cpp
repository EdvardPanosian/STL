#include "../Headers/array.hpp"
#include <array>
#include <iostream>

int main() {
    // Инициализация массива
    Array<int, 5> arr = {1, 2, 3, 4, 5};

    // Доступ через операторы
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Last element: " << arr[4] << std::endl;

    // Доступ через .at() (с проверкой выхода за пределы)
    std::cout << "Element at index 2: " << arr.at(2) << std::endl;

    // Доступ через .front() и .back()
    std::cout << "First element (front): " << arr.front() << std::endl;
    std::cout << "Last element (back): " << arr.back() << std::endl;

    // Использование .fill() для заполнения массива
    arr.fill(0);
    std::cout << "Array after fill(0): ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Итерация по массиву с begin() и end()
    std::cout << "Array elements via iterators: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Итерация по массиву в обратном порядке с rbegin() и rend()
    std::cout << "Array elements in reverse order: ";
    for (auto rit = arr.rbegin(); rit != arr.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // Сравнение массивов
    Array<int, 5> arr2 = {0, 0, 0, 0, 0};
    if (arr == arr2) {
        std::cout << "Arrays are equal" << std::endl;
    } else {
        std::cout << "Arrays are not equal" << std::endl;
    }

    // Печать размера и проверки на пустоту
    std::cout << "Array size: " << arr.size() << std::endl;
    if (arr.empty()) {
        std::cout << "Array is empty" << std::endl;
    }

    return 0;
}
