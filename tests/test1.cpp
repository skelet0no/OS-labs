#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include "../laba1/divider.h"

std::string runDivider(const std::string &input) {
    std::string tempFileName = "test_divider.txt";
    std::ofstream outFile(tempFileName);
    outFile << input;
    outFile.close();

    std::ostringstream buffer;
    std::streambuf *originalCout = std::cout.rdbuf(buffer.rdbuf());

    Divider(tempFileName);

    std::cout.rdbuf(originalCout);

    remove(tempFileName.c_str());

    return buffer.str();
}

TEST(Test, ValidDivision) {
    std::string input = "100 5 2\n50 4 5\n30 3 0\n80 8 2\n20 2 0";
    std::string expectedOutput = "Result: 10\nResult: 2\nError: ZeroDivision\nResult: 5\nError: ZeroDivision\n";

    EXPECT_EQ(runDivider(input), expectedOutput);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
