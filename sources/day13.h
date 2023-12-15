#ifndef AOC23_DAY13_H
#define AOC23_DAY13_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day13 {
private:
    string path;
public:
    Day13(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY13_H
