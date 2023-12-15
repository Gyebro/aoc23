#include <gtest/gtest.h>
#include "../sources/day09.h"

TEST(Day09, PartOneSample) {
Day09 day("test09.txt");
int sol = day.solve();
EXPECT_EQ(sol, 114);
}

TEST(Day09, PartOne) {
Day09 day("day09.txt");
int sol = day.solve();
EXPECT_EQ(sol, 2043183816);
}

TEST(Day09, PartTwoSample) {
Day09 day("test09.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 2);
}

TEST(Day09, PartTwo) {
Day09 day("day09.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 1118);
}