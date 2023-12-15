#include <gtest/gtest.h>
#include "../sources/day14.h"

TEST(Day14, PartOneSample) {
Day14 day("test14.txt");
int sol = day.solve();
EXPECT_EQ(sol, 136);
}

TEST(Day14, PartOne) {
Day14 day("day14.txt");
int sol = day.solve();
EXPECT_EQ(sol, 105623);
}

TEST(Day14, PartTwoSample) {
Day14 day("test14.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 64);
}

TEST(Day14, PartTwo) {
Day14 day("day14.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 98029);
}