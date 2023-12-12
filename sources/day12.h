#ifndef AOC23_DAY12_H
#define AOC23_DAY12_H


#include "utils.h"
#include <fstream>
#include <iostream>

class Day12 {
private:
    string path;
public:
    Day12(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY12_H
