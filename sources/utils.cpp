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

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

string trim_spaces(string value) {
    // Remove leading spaces
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), std::bind(std::not_equal_to<char>(), ' ', std::placeholders::_1)));
    // Remove trailing ones
    value.erase(std::find_if(value.rbegin(), value.rend(), std::bind(std::not_equal_to<char>(), ' ', std::placeholders::_1)).base(), value.end());
    return value;
}

bool contains_char(const string& s, const char c) {
    return (s.find(c) != std::string::npos);
}

string sanitize_spaces(string str) {
    str = trim_spaces(str);
    std::string::iterator new_end =
            std::unique(str.begin(), str.end(),
                        [](char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); }
            );
    str.erase(new_end, str.end());
    return str;
}

size_t lcm(size_t a, size_t b) {
    size_t hcf = a; // highest common factor
    size_t temp = b;
    while (hcf != temp) {
        if (hcf > temp)
            hcf -= temp;
        else
            temp -= hcf;
    }
    return (a / hcf) * b;
}

size_t lcm(size_t& a, size_t& b, size_t& c) {
    return lcm(lcm(a,b),lcm(a,c));
}