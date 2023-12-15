#include "day13.h"

class Pattern {
private:
    vector<string> map;
    vector<string> tmap;
    int find_mirror_rows(const vector<string>& m) {
        if (m.size() < 2) {
            return 0;
        } else {
            // Check for mirrors between (i and i+1)
            int total = 0;
            for (int i = 0; i < m.size()-1; i++) {
                bool mirror = true;
                for (int s = 1; s < min(static_cast<int>(m.size())-i, i+2); s++) { // i+s < m.size and i+1-s >= 0
                    // Compare i+1-s and i+s
                    if (m[i+s] == m[i+1-s]) {
                        // Continue
                    } else {
                        mirror = false;
                        break;
                    }
                }
                if (mirror) {
                    total += (i+1); // Shift between index and row/col number
                }
            }
            return total;
        }
    }
    int find_smudge_rows(const vector<string>& m) {
        if (m.size() < 2) {
            return 0;
        } else {
            // Check for mirrors between (i and i+1) with exactly one difference
            int total = 0;
            for (int i = 0; i < m.size()-1; i++) {
                size_t smudge_count = 0;
                for (int s = 1; s < min(static_cast<int>(m.size())-i, i+2); s++) { // i+s < m.size and i+1-s >= 0
                    // Compare i+1-s and i+s
                    for (size_t k=0; k<m[0].size(); k++) {
                        if (m[i+s][k] == m[i+1-s][k]) {
                            // Continue
                        } else {
                            smudge_count++;
                        }
                    }
                    if (smudge_count > 1) break;
                }
                if (smudge_count == 1) {
                    total += (i+1); // Shift between index and row/col number
                }
            }
            return total;
        }
    }
public:
    void add_line(const string& s) {
        map.push_back(s);
    }
    void update_transpose() {
        string line;
        line.resize(map.size());
        tmap.resize(map[0].size());
        std::fill(tmap.begin(), tmap.end(),line);
        for (size_t i=0; i<map.size(); i++) {
            for (size_t j=0; j<map[0].size(); j++) {
                tmap[j][i] = map[i][j];
            }
        }
    }
    void clear() {
        map.resize(0);
    }
    int find_mirrors() {
        return 100*find_mirror_rows(map) +
               find_mirror_rows(tmap);
    }
    int find_smudged_mirrors() {
        return 100*find_smudge_rows(map) +
                find_smudge_rows(tmap);
    }
    void print() const {
        for (const string& s : map) {
            cout << s << endl;
        }
        cout << endl;
    }
};

Day13::Day13(const string& inputpath) : path(inputpath) { }

int Day13::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t total = 0;
    vector<Pattern> patterns;
    if (infile.is_open()) {
        Pattern p;
        while (getline(infile, line)) {
            if (line.empty()) {
                patterns.push_back(p);
                p.clear();
            } else {
                p.add_line(line);
            }
        }
        patterns.push_back(p);
    }
    for (Pattern& p : patterns) {
        p.update_transpose();
        if (part_one) {
            total += p.find_mirrors();
        } else {
            total += p.find_smudged_mirrors();
        }
    }
    return total;
}
