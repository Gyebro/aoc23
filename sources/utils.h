#ifndef AOC23_UTILS_H
#define AOC23_UTILS_H

#include <string>
#include <algorithm>
#include <regex>
#include <functional>

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

template<class T>
bool contains(const vector<T>& c, const T& t) {
    for (const T& e : c) {
        if (e == t) return true;
    }
    return false;
}

bool contains_char(const string& s, const char c);

string sanitize_spaces(string str);

struct str_to_ul {
    unsigned long operator()(const string& s) {
        return stoul(s);
    }
};

struct str_to_int {
    int operator()(const string& s) {
        return stoi(s);
    }
};

struct str_to_int64 {
    int64_t operator()(const string& s) {
        return stoll(s);
    }
};

size_t lcm(size_t a, size_t b);

size_t lcm(size_t& a, size_t& b, size_t& c);

#endif //AOC23_UTILS_H
