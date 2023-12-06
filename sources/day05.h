#ifndef AOC23_DAY05_H
#define AOC23_DAY05_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day05 {
private:
    string path;
public:
    Day05(const string& inputpath);
    int solve(bool part_one = true) const;
};



#endif //AOC23_DAY05_H
