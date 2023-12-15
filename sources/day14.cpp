#include "day14.h"

enum ControlPanelDirection {
    North,
    South,
    East,
    West
};

class ControlPanel {
private:
    vector<string> map;
    size_t w;
    size_t h;
public:
    void add_row(const string& s) {
        map.push_back(s);
        w = map[0].size();
        h = map.size();
    }
    void tilt_rock(size_t i, size_t j, ControlPanelDirection dir) {
        bool rolling = false;
        int i_target, j_target;
        if ((dir == North) && (i > 0)) {
            // Go along i coordinate towards North (negative dir)
            j_target = j;
            for (int i_probe = static_cast<int>(i - 1); i_probe >= 0; i_probe--) {
                if (map[i_probe][j] == '.') {
                    rolling = true;
                    i_target = i_probe;
                } else {
                    break;
                }
            }
        } else if ((dir == South) && (i < h)) {
            // Go along i coordinate towards South (positive dir)
            j_target = j;
            for (int i_probe = static_cast<int>(i + 1); i_probe < h; i_probe++) {
                if (map[i_probe][j] == '.') {
                    rolling = true;
                    i_target = i_probe;
                } else {
                    break;
                }
            }
        } else if ((dir == West) && (j > 0)) {
            // Go along j coordinate towards West (negative dir)
            i_target = i;
            for (int j_probe = static_cast<int>(j - 1); j_probe >= 0; j_probe--) {
                if (map[i][j_probe] == '.') {
                    rolling = true;
                    j_target = j_probe;
                } else {
                    break;
                }
            }
        } else if ((dir == East) && (i < w)) {
            // Go along j coordinate towards East (positive dir)
            i_target = i;
            for (int j_probe = static_cast<int>(j + 1); j_probe < w; j_probe++) {
                if (map[i][j_probe] == '.') {
                    rolling = true;
                    j_target = j_probe;
                } else {
                    break;
                }
            }
        }
        if (rolling) {
            map[i_target][j_target] = 'O';
            map[i][j] = '.';
        }
    }
    void tilt(ControlPanelDirection dir) {
        switch (dir) {
            case North:
            case West:
                for (size_t i=0; i<h; i++) { for (size_t j=0; j<w; j++) { if (map[i][j] == 'O') { tilt_rock(i, j, dir); }}}
                break;
            case South:
                for (int i=h-1; i>=0; i--) { for (size_t j=0; j<w; j++) { if (map[i][j] == 'O') { tilt_rock(i, j, dir); }}}
                break;
            case East:
                for (size_t i=0; i<h; i++) { for (int j=w-1; j>=0; j--) { if (map[i][j] == 'O') { tilt_rock(i, j, dir); }}}
                break;
        }
    }
    size_t read_weight(ControlPanelDirection dir) {
        size_t weight = 0;
        for (size_t i=0; i<h; i++) {
            for (size_t j=0; j<w; j++) {
                if (map[i][j] == 'O') {
                    switch (dir) {
                        case North:
                            weight += (h-i);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        return weight;
    }
    void print() {
        cout << "Panel: " << endl;
        for (const string& s : map) {
            cout << s << endl;
        }
    }
    void tilt_cycle(const vector<ControlPanelDirection>& dirs) {
        for (const ControlPanelDirection& dir : dirs) {
            tilt(dir);
        }
        //print();
    }
};

Day14::Day14(const string& inputpath) : path(inputpath) { }

int Day14::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t total = 0;
    ControlPanel panel;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            panel.add_row(line);
        }
    }
    if (part_one) {
        panel.tilt(North);
        total = panel.read_weight(North);
    } else {
        // Part two
        vector<ControlPanelDirection> cycle = {North, West, South, East};
        // Try to find a period in the whole system.
        // Check load values
        bool period_found = false;
        size_t transient = 500;
        size_t exit_cond = 10000;
        size_t max_period = 300;
        size_t period = 0;
        size_t c = 0;
        vector<size_t> weight_cycle;
        vector<size_t> weights;
        while (!period_found) {
            panel.tilt_cycle(cycle);
            size_t w = panel.read_weight(North);
            weights.push_back(w);
            c++;
            if (c > transient) {
                // Try to find period from the back
                for (size_t p = 2; p < max_period; p++) {
                    vector<size_t> w0, w1;
                    w0.insert(w0.begin(), weights.rbegin(), weights.rbegin()+p);
                    w1.insert(w1.begin(), weights.rbegin()+p, weights.rbegin()+2*p);
                    if (w0 == w1) {
                        period_found = true;
                        period = p;
                        std::reverse(w0.begin(), w0.end());
                        weight_cycle = w0;
                        break;
                    }
                }
            }
            if (c > exit_cond) break;
        }
        if (period_found) {
            // Calculate 10^9th element
            size_t target_idx = 1000000000;
            size_t modulo = (target_idx-c-1) % period;
            total = weight_cycle[modulo];
        } else {
            total = 0;
            cout << "Error: period not found" << endl;
        }
    }
    return total;
}