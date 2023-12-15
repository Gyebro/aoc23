#include <gtest/gtest.h>
#include "../sources/day02.h"

TEST(Day02, PartOneSample) {
Day02 day("test02.txt");
int sol = day.solve();
EXPECT_EQ(sol, 8);
}

TEST(Day02, PartOne) {
Day02 day("day02.txt");
int sol = day.solve();
EXPECT_EQ(sol, 1853);
}

TEST(Day02, PartTwoSample) {
Day02 day("test02.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 2286);
}

TEST(Day02, PartTwo) {
Day02 day("day02.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 72706);
}