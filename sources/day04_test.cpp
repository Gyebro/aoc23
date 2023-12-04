#include <gtest/gtest.h>
#include "day04.h"

TEST(Day04, PartOneSample) {
Day04 day("test04.txt");
int sol = day.solve();
EXPECT_EQ(sol, 13);
}

TEST(Day04, PartOne) {
Day04 day("day04.txt");
int sol = day.solve();
EXPECT_EQ(sol, 23673);
}

TEST(Day04, PartTwoSample) {
Day04 day("test04.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 30);
}

TEST(Day04, PartTwo) {
Day04 day("day04.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 12263631);
}