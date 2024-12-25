#include <iostream>
#include <cmath>
#include "cards.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <number_of_rounds> <max_threads>" << std::endl;
        return 1;
    }

    int numRounds = std::stoi(argv[1]);
    int maxThreads = std::stoi(argv[2]);
    if (numRounds <= 0 || maxThreads <= 0) {
        std::cerr << "Both number of rounds and number of threads must be positive integers." << std::endl;
        return 1;
    }

    double solver = cards(numRounds, maxThreads);

    std::cout << "Probability of the top two cards being the same: " << round(solver * 1000) / 1000 << std::endl;
}