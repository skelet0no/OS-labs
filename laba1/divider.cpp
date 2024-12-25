#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>

void Divider(const std::string &fileName) {
    std::string line;

    std::ifstream infile(fileName);
    
    while (std::getline(infile, line)) {
        pid_t pid = fork();

        if (pid == 0) {
            execl("./child", const_cast<char *>(line.c_str()), nullptr);
            perror("Failed");
            exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            std::ifstream tempFile;
            tempFile.open("temp.txt");
            std::string num;
            std::getline(tempFile, num);
            if (num == "-1") {
                std::cout << "Error: ZeroDivision\n";
            } else if (num == "-2") {
                std::cout << "\n";
            } else {
                std::cout << "Result: " << num << "\n";
            }   
        } else {
            std::cout << "Error: CreateProcess\n";
            infile.close();
            return;
        }
    }

    infile.close();
    return;
}
