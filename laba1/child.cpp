#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int ProcessCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<int> numbers;
    int num, answer;
    
    while (iss >> num) {
        numbers.push_back(num);
    }

    if (numbers.empty()) return -2;

    answer = numbers[0];

    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == 0) {
            return -1;
        }
        answer /= numbers[i];
    }
    return answer;
}