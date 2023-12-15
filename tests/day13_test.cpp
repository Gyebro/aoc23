#include <gtest/gtest.h>
#include "../sources/day13.h"

TEST(Day13, PartOneSample) {
Day13 day("test13.txt");
int sol = day.solve();
EXPECT_EQ(sol, 405);
}

TEST(Day13, PartOne) {
Day13 day("day13.txt");
int sol = day.solve();
EXPECT_EQ(sol, 26957);
}

TEST(Day13, PartTwoSample) {
Day13 day("test13.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 400);
}

TEST(Day13, PartTwo) {
Day13 day("day13.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 42695);
}