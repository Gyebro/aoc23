#include <valarray>
#include <numeric>
#include "day12.h"

string sanitize_dots(const string& s) {
    string wspaces = replace_substring(s,"\\."," ");
    return sanitize_spaces(wspaces);
}

class ConditionRecord {
private:
    string springs;
    vector<size_t> groups;
    // Check a record without unknowns against groups
    bool checkKnownRecord(const string& s) const {
        string spacesep = sanitize_dots(s);
        vector<string> spring_groups = split(spacesep, ' ');
        vector<size_t> counts;
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
        vector<size_t> new_groups;
        new_groups.reserve( groups.size()*mult ); // preallocate memory
        for (size_t i=0; i<mult; i++) {
            new_springs += springs;
            new_groups.insert(new_groups.end(), groups.begin(), groups.end());
        }
        springs = new_springs;
        groups = new_groups;
    }
    size_t getPossibleArrangements() const {
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
        //cout << "Generating a total of " << pow(2, loc.size()) <<  " combinations\n";
        /*cout << springs << "\t\t";
        for (const size_t& s : groups) cout << s << " ";
        cout << endl;*/

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
        //cout << total << endl;
        return total;
    }
};

Day12::Day12(const string& inputpath) : path(inputpath) { }

int Day12::solve(bool part_one) const {
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

int main() {
    //Day12 day("test12.txt");
    Day12 day("day12.txt");
    cout << "Day12 Part one: " << day.solve() << endl;
    //cout << "Day12 Part two: " << day.solve(false) << endl;
    return 0;
}