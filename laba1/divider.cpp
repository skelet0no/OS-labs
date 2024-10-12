#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include "child.h"

void Divider(std::string fileName) {
    std::string line;
    std::string number;

    std::ifstream infile(fileName);
    
    while (std::getline(infile, line)) {
        pid_t pid = fork();
        int num;

        if (pid == 0) {
            num = ProcessCommand(line);
            if (num != -1) {
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            wait(nullptr);
        } else {
            std::cout << "Error: CreateProcess\n";
            infile.close();
            return;
        }
        number = std::to_string(ProcessCommand(line));
        if (number == "-1") {
            std::cout << "Error: ZeroDivision\n";
        } else if (number == "-2") {
            std::cout << "\n";
        } else {
            std::cout << "Result: " << number << "\n";
        }
    }

    infile.close();
    return;
}
