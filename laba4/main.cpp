#include <istream>
#include <vector>
#include <iostream>
#include <functional>
#include "lib1.h"
#include "lib2.h"

void handlePrimeNumbers(const std::function<int(int A, int B)>& CalcNums, std::istream& is, std::ostream& os) {
    int a, b;

    os << "Enter a and b: ";
    is >> a >> b;

    int result = CalcNums(a, b);
    os << "Result: " << result << std::endl;
}

void handleSort(const std::function<std::vector<int> (std::vector<int>)>& SortingMethod, std::istream& is, std::ostream& os) {
    std::vector<int> numsList;
    size_t size;

    os << "Enter the size of the array: ";
    is >> size;

    os << "Enter the array elements separated by a space: ";
    int val;
    for (auto i = 0; i < size; ++i){
        is >> val;
        numsList.push_back(val);
    }

    auto result = SortingMethod(numsList);
    os << "Result: ";
    for (auto& item: result) os << item << " " << std::endl;
}

int main() {
    int command = 0;
    std::istream& is = std::cin;
    std::ostream& os = std::cout;
    while (command != 5) {
        os << "Enter command: ";
        is >> command;

        switch (command) {
            case 1:
                handlePrimeNumbers(SimplePrimeNumbers, is, os);
            break;
            case 2:
                handlePrimeNumbers(HardPrimeNumbers, is, os);
            break;
            case 3:
                handleSort(HoarSort, is, os);
            break;
            case 4:
                handleSort(BubbleSort, is, os);
            break;
            default:
                break;
        }

        if (command == 5) return 0;
    }
}
