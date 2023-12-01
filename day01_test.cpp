#include <gtest/gtest.h>
#include "day01.h"

TEST(Day01, PartOneSample) {
    Day01 day("test01.txt");
    int sol = day.solve();
    EXPECT_EQ(sol, 142);
}

TEST(Day01, PartOne) {
    Day01 day("day01.txt");
    int sol = day.solve();
    EXPECT_EQ(sol, 54927);
}

TEST(Day01, PartTwoSample) {
    Day01 day("test01b.txt");
    int sol = day.solve(false);
    EXPECT_EQ(sol, 281);
}

TEST(Day01, PartTwo) {
    Day01 day("day01.txt");
    int sol = day.solve(false);
    EXPECT_EQ(sol, 54581);
}