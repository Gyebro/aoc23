#ifndef AOC23_DAY06_H
#define AOC23_DAY06_H


#include "utils.h"
#include <fstream>
#include <iostream>

class Day06 {
private:
    string path;
public:
    Day06(const string& inputpath);
    int solve(bool part_one = true) const;
};



#endif //AOC23_DAY06_H
