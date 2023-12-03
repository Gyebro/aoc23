#ifndef AOC23_UTILS_H
#define AOC23_UTILS_H

#include <string>
#include <algorithm>
#include <regex>

using namespace std;

string replace_substring(const string &str, const string &target, const string &repl);

void find_replace_at_pos(string& line, const size_t pos, const string& match, const string& repl);

template<class T>
void split(const std::string &s, char delim, T result) {
    stringstream ss(s); string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim);

string trim_spaces(string value);

#endif //AOC23_UTILS_H
