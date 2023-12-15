#include <gtest/gtest.h>
#include "../sources/day07.h"

TEST(Day07, PartOneSample) {
Day07 day("test07.txt");
int sol = day.solve();
EXPECT_EQ(sol, 6440);
}

TEST(Day07, PartOne) {
Day07 day("day07.txt");
int sol = day.solve();
EXPECT_EQ(sol, 252656917);
}

TEST(Day07, PartTwoSample) {
Day07 day("test07.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 5905);
}

TEST(Day07, PartTwo) {
Day07 day("day07.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 253499763);
}