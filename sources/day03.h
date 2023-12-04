#ifndef AOC23_DAY03_H
#define AOC23_DAY03_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day03 {
private:
    string path;
public:
    Day03(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY03_H
