#ifndef AOC23_DAY10_H
#define AOC23_DAY10_H


#include "utils.h"
#include <fstream>
#include <iostream>

class Day10 {
private:
    string path;
public:
    Day10(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY10_H
