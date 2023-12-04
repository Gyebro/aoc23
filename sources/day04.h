#ifndef AOC23_DAY04_H
#define AOC23_DAY04_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day04 {
private:
    string path;
public:
    Day04(const string& inputpath);
    int solve(bool part_one = true) const;
};


#endif //AOC23_DAY04_H
