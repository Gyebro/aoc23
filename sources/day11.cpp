#include "day11.h"

class Day11Map {
private:
    vector<string> map;
    vector<pair<int, int>> galaxies;
    vector<size_t> empty_rows;
    vector<size_t> empty_cols;
    size_t mult;
    [[deprecated]]
    void expand_rows() {
        string empty;
        empty.resize(map[0].size());
        std::fill(empty.begin(), empty.end(), '.');
        for (auto it = map.begin(); it != map.end(); it++) {
            if (*it == empty) {
                map.insert(it,empty);
                it++;
            }
        }
    }
    [[deprecated]]
    void expand_cols() {
        size_t h = map.size();
        for (size_t col=0; col<map[0].size(); col++) {
            bool empty = true;
            for (size_t r=0; r<h; r++) {
                if (map[r][col] != '.') {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                for (size_t r=0; r<h; r++) {
                    map[r].insert(col, ".");
                }
                col++;
            }
        }
    }
    int get_manhattan_distance(size_t gi, size_t gj) {
        // Calculate along i
        int mini = min(galaxies[gi].first, galaxies[gj].first);
        int maxi = max(galaxies[gi].first, galaxies[gj].first);
        int disti = maxi - mini;
        for (size_t i = mini; i<maxi; i++) {
            if (contains(empty_rows, i)) disti += (mult - 1);
        }
        int minj = min(galaxies[gi].second, galaxies[gj].second);
        int maxj = max(galaxies[gi].second, galaxies[gj].second);
        int distj = maxj-minj;
        for (size_t j = minj; j<maxj; j++) {
            if (contains(empty_cols, j)) distj += (mult-1);
        }
        return disti+distj;
    }
public:
    void add_line(const string& s) {
        map.push_back(s);
    }
    void expand(size_t m = 2) {
        // Part 1 approach: actually expand the map
        //expand_rows();
        //expand_cols();
        // Part 2 approach: mark empty_str rows & cols, count extra during manhattan distance calc
        mult = m;
        string empty_str;
        empty_str.resize(map[0].size());
        std::fill(empty_str.begin(), empty_str.end(), '.');
        for (size_t i = 0; i<map.size(); i++) {
            if (map[i] == empty_str) empty_rows.push_back(i);
        }
        for (size_t j=0; j < map[0].size(); j++) {
            bool empty = true;
            for (auto & r : map) {
                if (r[j] != '.') {
                    empty = false; break;
                }
            }
            if (empty) {
                empty_cols.push_back(j);
            }
        }
    }
    void print() {
        for (const string& s : map) {
            cout << s << endl;
        }
    }
    void mark_galaxies() {
        for (size_t i=0; i<map.size(); i++) {
            for (size_t j=0; j<map[0].size(); j++) {
                if (map[i][j] == '#') galaxies.emplace_back(i,j);
            }
        }
    }
    int64_t get_total_manhattan_distance() {
        int64_t total_dist = 0;
        for (size_t i=0; i<galaxies.size()-1; i++) {
            for (size_t j=i+1; j<galaxies.size(); j++) {
                //int dis0 = abs(galaxies[i].first-galaxies[j].first) + abs(galaxies[i].second-galaxies[j].second);
                int dist = get_manhattan_distance(i, j);
                total_dist += dist;
            }
        }
        return total_dist;
    }
};

Day11::Day11(const string& inputpath) : path(inputpath) { }

int64_t Day11::solve(bool part_one) const {
    string line;
    ifstream infile(path);

    Day11Map map;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            map.add_line(line);
        }
    }
    if (part_one) {
        map.expand();
    } else {
        map.expand(1000000);
    }
    map.mark_galaxies();
    int64_t total = map.get_total_manhattan_distance();
    return total;
}

int main() {
    //Day11 day("test11.txt");
    Day11 day("day11.txt");
    cout << "Day11 Part one: " << day.solve() << endl;
    cout << "Day11 Part two: " << day.solve(false) << endl;
    return 0;
}