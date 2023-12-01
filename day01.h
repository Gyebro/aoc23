#ifndef AOC23_DAY01_H
#define AOC23_DAY01_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day01 {
private:
    string path;
public:
    Day01(const string& inputpath);
    int solve(bool part_one = true) const;
};

#endif //AOC23_DAY01_H
