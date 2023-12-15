#ifndef AOC23_DAY16_H
#define AOC23_DAY16_H


#include "utils.h"
#include <fstream>
#include <iostream>

class Day16 {
private:
    string path;
public:
    Day16(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY16_H
