#ifndef AOC23_DAY08_H
#define AOC23_DAY08_H

#include "utils.h"
#include <fstream>
#include <iostream>

class Day08 {
private:
    string path;
public:
    Day08(const string& inputpath);
    size_t solve(bool part_one = true) const;
};


#endif //AOC23_DAY08_H
