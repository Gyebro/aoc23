#include <gtest/gtest.h>
#include "../sources/day12.h"

TEST(Day12, PartOneSample) {
Day12 day("test12.txt");
size_t sol = day.solve();
EXPECT_EQ(sol, 21);
}

TEST(Day12, PartOne) {
Day12 day("day12.txt");
size_t sol = day.solve();
EXPECT_EQ(sol, 6949);
}

TEST(Day12, PartTwoSample) {
Day12 day("test12.txt");
size_t sol = day.solve(false);
EXPECT_EQ(sol, 525152);
}

TEST(Day12, PartTwo) {
Day12 day("day12.txt");
size_t sol = day.solve(false);
EXPECT_EQ(sol, 51456609952403);
}