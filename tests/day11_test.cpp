#include <gtest/gtest.h>
#include "../sources/day11.h"

TEST(Day11, PartOneSample) {
Day11 day("test11.txt");
int sol = day.solve();
EXPECT_EQ(sol, 374);
}

TEST(Day11, PartOne) {
Day11 day("day11.txt");
int sol = day.solve();
EXPECT_EQ(sol, 9627977);
}

TEST(Day11, PartTwoSample) {
Day11 day("test11.txt");
size_t sol = day.solve(false);
EXPECT_EQ(sol, 82000210);
}

TEST(Day11, PartTwo) {
Day11 day("day11.txt");
size_t sol = day.solve(false);
EXPECT_EQ(sol, 644248339497);
}