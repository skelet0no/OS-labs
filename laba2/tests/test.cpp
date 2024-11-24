#include <gtest/gtest.h>
#include <chrono>
#include "../cards.h"

TEST(CardsTest, SingleThreaded) {
    int rounds = 1000000;
    double result = cards(rounds, 1);
    EXPECT_NEAR(result, 0.059, 0.005);
}

TEST(CardsTest, MultiThreadedEqualsSingleThreaded) {
    int rounds = 1000000;

    double singleThreadResult = cards(rounds, 1);
    double multiThreadedResult = cards(rounds, 4);

    EXPECT_NEAR(singleThreadResult, multiThreadedResult, 0.005);
}

TEST(CardsTest, MultiThreadedFasterThanSingleThreaded) {
    int rounds = 1000000;

    auto startSingle = std::chrono::high_resolution_clock::now();
    double singleThreadResult = cards(rounds, 1);
    auto endSingle = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> singleDuration = endSingle - startSingle;

    auto startMulti = std::chrono::high_resolution_clock::now();
    double multiThreadedResult = cards(rounds, 4);
    auto endMulti = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> multiDuration = endMulti - startMulti;
    EXPECT_TRUE(multiDuration.count() < singleDuration.count());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}