#ifndef AOC23_DAY09_H
#define AOC23_DAY09_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day09 {
private:
    string path;
public:
    Day09(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY09_H
