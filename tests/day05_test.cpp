#include <gtest/gtest.h>
#include "../sources/day05.h"

TEST(Day05, PartOneSample) {
    Day05 day("test05.txt");
    int sol = day.solve();
    EXPECT_EQ(sol, 35);
}

TEST(Day05, PartOne) {
    Day05 day("day05.txt");
    int sol = day.solve();
    EXPECT_EQ(sol, 177942185);
}

TEST(Day05, PartTwoSample) {
    Day05 day("test05.txt");
    int sol = day.solve(false);
    EXPECT_EQ(sol, 46);
}

TEST(Day05, PartTwo) {
    Day05 day("day05.txt");
    int sol = day.solve(false);
    EXPECT_EQ(sol, 69841803);
}