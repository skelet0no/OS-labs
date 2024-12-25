#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argv, char ** argc) {
    std::ofstream tempFile;
    tempFile.open("temp.txt");
    std:: string command = argc[0];
    std::istringstream iss(command);
    std::vector<int> numbers;
    int num, answer;
    
    while (iss >> num) {
        numbers.push_back(num);
    }

    if (numbers.empty()) {
        tempFile << "-2" << std::endl;
        tempFile.close();
        return 0;
    }

    answer = numbers[0];

    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == 0) {
            tempFile << "-1" << std::endl;
            tempFile.close();
            return 0;
        }
        answer /= numbers[i];
    }
    tempFile << answer << std::endl;
    tempFile.close();
    return 0;
}