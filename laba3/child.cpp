#include "child.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <csignal>

#define SHM_NAME "/shm_example"
#define SHM_SIZE 1024

void handleError(const std::string& message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

std::vector<int> parseNumbers(const std::string& line) {
    std::istringstream iss(line);
    std::vector<int> numbers;
    int num;

    while (iss >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

std::string processLine(const std::string& line) {
    std::vector<int> numbers = parseNumbers(line);

    if (numbers.size() < 2) {
        return "Error: Invalid input\n";
    }

    int result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == 0) {
            return "Error: ZeroDivision\n";
        }
        result /= numbers[i];
    }

    return std::to_string(result) + "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./child <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        handleError("shm_open");
    }
    void* shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        handleError("mmap");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string result = processLine(line);
        sprintf(static_cast<char*>(shm_ptr), "%s", result.c_str());
        kill(getppid(), SIGUSR1);
        usleep(100000);
    }

    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        handleError("munmap");
    }
    close(shm_fd);

    return 0;
}
