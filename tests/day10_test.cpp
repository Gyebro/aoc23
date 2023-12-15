#include <gtest/gtest.h>
#include "../sources/day10.h"

TEST(Day10, PartOneSample) {
Day10 day("test10.txt");
int sol = day.solve();
EXPECT_EQ(sol, 8);
}

TEST(Day10, PartOne) {
Day10 day("day10.txt");
int sol = day.solve();
EXPECT_EQ(sol, 6828);
}

TEST(Day10, PartTwoSample) {
Day10 day("test10b.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 8);
}

TEST(Day10, PartTwo) {
Day10 day("day10.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 459);
}