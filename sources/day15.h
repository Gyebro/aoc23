#ifndef AOC23_DAY15_H
#define AOC23_DAY15_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day15 {
private:
    string path;
public:
    Day15(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY15_H
