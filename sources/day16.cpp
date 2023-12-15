#include "day16.h"

Day16::Day16(const string& inputpath) : path(inputpath) { }

int Day16::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t total = 0;
    if (infile.is_open()) {
        while (getline(infile, line)) {
        }
    }
    return total;
}

int main() {
    Day16 day("test16.txt");
    //Day16 day("day16.txt");
    cout << "Day16 Part one: " << day.solve() << endl;
    //cout << "Day16 Part two: " << day.solve(false) << endl;
    return 0;
}