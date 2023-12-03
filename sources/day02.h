#ifndef AOC23_DAY02_H
#define AOC23_DAY02_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day02 {
private:
    string path;
public:
    Day02(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY02_H
