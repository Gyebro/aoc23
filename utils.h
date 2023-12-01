#ifndef AOC23_UTILS_H
#define AOC23_UTILS_H

#include <string>
#include <algorithm>
#include <regex>

using namespace std;

string replace_substring(const string &str, const string &target, const string &repl);

void find_replace_at_pos(string& line, const size_t pos, const string& match, const string& repl);

#endif //AOC23_UTILS_H
