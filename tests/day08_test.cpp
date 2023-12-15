#include <gtest/gtest.h>
#include "../sources/day08.h"

TEST(Day08, PartOneSample) {
Day08 day("test08.txt");
int sol = day.solve();
EXPECT_EQ(sol, 2);
}

TEST(Day08, PartOneSampleTwo) {
Day08 day("test08b.txt");
int sol = day.solve();
EXPECT_EQ(sol, 6);
}

TEST(Day08, PartOne) {
Day08 day("day08.txt");
int sol = day.solve();
EXPECT_EQ(sol, 20221);
}

TEST(Day08, PartTwoSample) {
Day08 day("test08c.txt");
int sol = day.solve(false);
EXPECT_EQ(sol, 6);
}

TEST(Day08, PartTwo) {
Day08 day("day08.txt");
size_t sol = day.solve(false);
EXPECT_EQ(sol, 14616363770447);
}