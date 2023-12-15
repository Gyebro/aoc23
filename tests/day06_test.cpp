#include <gtest/gtest.h>
#include "../sources/day06.h"

TEST(Day06, PartOneSample) {
Day06 day("test06.txt");
int sol = day.solve();
EXPECT_EQ(sol, 288);
}

TEST(Day06, PartOne) {
Day06 day("day06.txt");
int sol = day.solve();
EXPECT_EQ(sol, 227850);
}

TEST(Day06, PartTwoSample) {
Day06 day("test06.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 71503);
}

TEST(Day06, PartTwo) {
Day06 day("day06.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 42948149);
}