#include "day01.h"

int main () {
    Day01 day01("day01.txt");
    cout << "Part one solution: " << day01.solve() << endl;
    cout << "Part two solution: " << day01.solve(false) << endl;
    return 0;
}