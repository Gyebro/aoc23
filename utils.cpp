#include "utils.h"

string replace_substring(const string &str, const string &target, const string &repl) {
    regex regexPattern(target);
    return regex_replace(str, regexPattern, repl);
}

void find_replace_at_pos(string& line, const size_t pos, const string& match, const string& repl) {
    string test = line.substr(pos, match.length());
    if (test == match) {
        line.replace(pos, match.length(), repl);
    }
}