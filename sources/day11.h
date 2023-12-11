#ifndef AOC23_DAY11_H
#define AOC23_DAY11_H


#include "utils.h"
#include <fstream>
#include <iostream>

class Day11 {
private:
    string path;
public:
    Day11(const string& inputpath);
    int64_t solve(bool part_one = true) const;
};


#endif //AOC23_DAY11_H
