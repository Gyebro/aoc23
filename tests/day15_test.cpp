#include <gtest/gtest.h>
#include "../sources/day15.h"

TEST(Day15, PartOneSample) {
Day15 day("test15.txt");
int sol = day.solve();
EXPECT_EQ(sol, 1320);
}

TEST(Day15, PartOne) {
Day15 day("day15.txt");
int sol = day.solve();
EXPECT_EQ(sol, 514394);
}

TEST(Day15, PartTwoSample) {
Day15 day("test15.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 145);
}

TEST(Day15, PartTwo) {
Day15 day("day15.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 236358);
}