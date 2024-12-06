#include <gtest/gtest.h>
#include <random>
#include "../lib1.h"
#include "../lib2.h"

constexpr int size = 10;

TEST(BubbleSortTests, Sorting){
    std::vector vector = {1, 10, 5, 2, 7};

    auto result = BubbleSort(vector);
    std::sort(vector.begin(), vector.end());

    EXPECT_EQ(result, vector);
}

TEST(HoarSortTests, Sorting){
    std::vector vector = {1, 10, 5, 2, 7};

    auto result = HoarSort(vector);
    std::sort(vector.begin(), vector.end());

    EXPECT_EQ(result, vector);
}

TEST(PrimeNumbersTests, SimpleCorrectCount){
    EXPECT_EQ(SimplePrimeNumbers(5, 15), 4);
}

TEST(PrimeNumbersTests, HardCorrectCount){
    EXPECT_EQ(HardPrimeNumbers(5, 15), 4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
