#include "../child.h"
#include <gtest/gtest.h>

TEST(ParseNumbersTest, HandlesEmptyString) {
    std::vector<int> result = parseNumbers("");
    EXPECT_TRUE(result.empty());
}

TEST(ParseNumbersTest, HandlesSingleNumber) {
    std::vector<int> result = parseNumbers("42");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 42);
}

TEST(ParseNumbersTest, HandlesMultipleNumbers) {
    std::vector<int> result = parseNumbers("1 2 3");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(ProcessLineTest, HandlesInvalidInput) {
    std::string result = processLine("42");
    EXPECT_EQ(result, "Error: Invalid input\n");
}

TEST(ProcessLineTest, HandlesZeroDivision) {
    std::string result = processLine("4 0");
    EXPECT_EQ(result, "Error: ZeroDivision\n");
}

TEST(ProcessLineTest, HandlesValidInput) {
    std::string result = processLine("8 2 2");
    EXPECT_EQ(result, "2\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
