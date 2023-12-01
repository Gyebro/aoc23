#include "day01.h"

static const string letters = "abcdefghijklmnopqrstuvwxyz";

int day01_process_line(string& line) {
    for (char c : letters) {
        line.erase(std::remove(line.begin(), line.end(), c), line.end());
    }
    if (!line.empty()) {
        return stoi(line.substr(0,1) + line.substr(line.size()-1,1));
    } else {
        return 0;
    }
}

int day01_extract_digit(string& line, bool first = true) {
    for (char c : letters) {
        line.erase(std::remove(line.begin(), line.end(), c), line.end());
    }
    if (first) {
        return stoi(line.substr(0,1));
    } else { // last
        return stoi(line.substr(line.size()-1,1));
    }
}

void day01_replace_spelled_words_at_pos(string& line, int pos) {
    find_replace_at_pos(line, pos, "one",   "1");
    find_replace_at_pos(line, pos, "two",   "2");
    find_replace_at_pos(line, pos, "three", "3");
    find_replace_at_pos(line, pos, "four",  "4");
    find_replace_at_pos(line, pos, "five",  "5");
    find_replace_at_pos(line, pos, "six",   "6");
    find_replace_at_pos(line, pos, "seven", "7");
    find_replace_at_pos(line, pos, "eight", "8");
    find_replace_at_pos(line, pos, "nine",  "9");
    // Note: zero is not a valid spelled out digit
}

void day01_interpret_line(string& line, bool ltr = true) {
    // Note: left-to-right order for "first" digit: E.g. eightwothree must be 8wo3, not eigh23
    // right-to-left order for "last" digit: threeightwo must be 3igh2!
    if (ltr) {
        for (size_t pos = 0; pos < line.size(); pos++) {
            // Check for spelled out digits starting at this pos in line
            day01_replace_spelled_words_at_pos(line, pos);
        }
    } else { // rtl
        for (int pos = static_cast<int>(line.size())-1; pos >= 0; pos--) {
            // Check for spelled out digits starting at this pos in line
            day01_replace_spelled_words_at_pos(line, pos);
        }
    }
}

int day01_true_first_digit(string line, bool first = true) {
    day01_interpret_line(line, first);
    return day01_extract_digit(line, first);
}

Day01::Day01(const string& inputpath) : path(inputpath) { }

int Day01::solve(bool part_one) const {
    int sum = 0;
    string line;
    ifstream infile(path);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (part_one) {
                sum += day01_process_line(line);
            } else {
                int f = day01_true_first_digit(line, true);
                int l = day01_true_first_digit(line, false);
                sum += 10 * f + l;
            }
        }
        infile.close();
    }
    return sum;
}