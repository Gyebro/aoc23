#include <valarray>
#include <numeric>
#include "day12.h"

string sanitize_dots(const string& s) {
    string wspaces = replace_substring(s,"\\."," ");
    return sanitize_spaces(wspaces);
}

size_t valid_combinations(string s, deque<size_t> c, map<pair<string, deque<size_t>>, size_t>& table) {
    // If this function call is cached, return solution
    auto it = table.find(make_pair(s, c));
    if (it != table.end()) {
        return it->second;
    }
    // Remove leading dots
    s.erase(s.begin(), find_if(s.begin(), s.end(), bind(std::not_equal_to<>(), '.', std::placeholders::_1)));
    if (s.empty()) { // empty string and empty counts
        if (c.empty()) return 1;
        else return 0;
    }
    if (c.empty()) { // empty counts are valid if s does not contain #
        if (!contains_char(s, '#')) return 1;
        else return 0;
    }
    // s starts with '#' so remove the first spring
    if (s[0] == '#') {
        if ((s.size() < c[0]) || (contains_char(s.substr(0, c[0]),'.'))) {
            return 0; // not enough space for the spring group
        } else if (s.size() == c[0]) {
            return ((c.size() == 1) ? 1 : 0);  // single spring, right size
        } else if (s[c[0]] == '#') {
            return 0; // spring groups must be separate
        } else {
            s = s.substr(c[0]+1);
            c.pop_front();
            size_t sol = valid_combinations(s, c, table); // one less spring
            // Cache and return
            table[make_pair(s,c)] = sol; return sol;
        }
    }

    // first char is '?', branch off to '#' or '.' (no need to prepend '.' as it is dropped)
    size_t sol = valid_combinations("#"+s.substr(1), c, table) + valid_combinations(s.substr(1), c, table);
    // Cache and return
    table[make_pair(s,c)] = sol; return sol;
}

class ConditionRecord {
private:
    string springs;
    deque<size_t> groups;
    // Check a record without unknowns against groups
    bool checkKnownRecord(const string& s) const {
        string spacesep = sanitize_dots(s);
        vector<string> spring_groups = split(spacesep, ' ');
        deque<size_t> counts;
        std::transform(spring_groups.begin(), spring_groups.end(), back_inserter(counts), [](const string& s) -> size_t { return s.size(); });
        return counts == groups;
    }
public:
    ConditionRecord(const string& line) {
        vector<string> parts = split(line, ' ');
        springs = parts[0];
        vector<string> nums = split(parts[1], ',');
        std::transform(nums.begin(), nums.end(), back_inserter(groups), str_to_ul());
    }
    void unfold(const size_t mult) {
        string new_springs;
        deque<size_t> new_groups;
        for (size_t i=0; i<mult; i++) {
            new_springs += springs;
            if (i < mult-1) new_springs += "?";
            new_groups.insert(new_groups.end(), groups.begin(), groups.end());
        }
        springs = new_springs;
        groups = new_groups;
    }
    size_t getPossibleArrangements() const {
        map<pair<string, deque<size_t>>, size_t> table;
        return valid_combinations(springs, groups, table);
    }
    size_t getPossibleArrangementsOld() const {
        // Initial approach: brute force, since the number of unknowns N isn't "that high", (combinations to test is 2^N)
        size_t total = 0;
        string base_springs = replace_substring(springs, "\\?", ".");

        // Find unknowns
        vector<size_t> loc;
        size_t d_base = 0; // Damaged springs in base (if all unknowns are operating)
        for (size_t i=0; i<springs.size(); i++) {
            if (springs[i] == '?') loc.push_back(i);
            if (springs[i] == '#') d_base++;
        }

        // Expected total of d. springs
        size_t d_expected = accumulate(groups.begin(), groups.end(), 0);

        // Generate all 2^N combinations (N = loc.size) and test them.
        // For combination k, the binary "digits" mark locations of working springs (1) and damaged springs (0)
        for (size_t i=0; i<pow(2, loc.size()); i++) {
            bitset<32> b(i);
            // Pruning: number of d. springs should be equal to expected
            if (b.count() + d_base == d_expected) {
                string to_test = base_springs;
                for (size_t k = 0; k < loc.size(); k++) {
                    if (b[k]) to_test[loc[k]] = '#';
                }
                if (checkKnownRecord(to_test)) {
                    total++;
                }
            }
        }
        return total;
    }
};

Day12::Day12(const string& inputpath) : path(inputpath) { }

size_t Day12::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t total = 0;
    vector<ConditionRecord> records;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            records.emplace_back(line);
        }
    }
    for (auto& r : records) {
        if (!part_one) r.unfold(5);
        total += r.getPossibleArrangements();
    }
    return total;
}