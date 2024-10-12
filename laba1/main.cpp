#include <iostream>
#include <string>
#include "divider.h"

int main(){
    std::string fileName;

    std::cout << "Enter .txt file name:" << std::endl;
    std::getline(std::cin, fileName);
    Divider(fileName);
}
