#ifndef AOC23_DAY14_H
#define AOC23_DAY14_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day14 {
private:
    string path;
public:
    Day14(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY14_H
