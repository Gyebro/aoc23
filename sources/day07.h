#ifndef AOC23_DAY07_H
#define AOC23_DAY07_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day07 {
private:
    string path;
public:
    Day07(const string& inputpath);
    int solve(bool part_one = true) const;
};

#endif //AOC23_DAY07_H
