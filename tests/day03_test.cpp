#include <gtest/gtest.h>
#include "../sources/day03.h"

TEST(Day03, PartOneSample) {
Day03 day("test03.txt");
int sol = day.solve();
EXPECT_EQ(sol, 4361);
}

TEST(Day03, PartOne) {
Day03 day("day03.txt");
int sol = day.solve();
EXPECT_EQ(sol, 540212);
}

TEST(Day03, PartTwoSample) {
Day03 day("test03.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 467835);
}

TEST(Day03, PartTwo) {
Day03 day("day03.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 87605697);
}