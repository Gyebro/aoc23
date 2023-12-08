#include "day08.h"

class Day08Segment {
public:
    string name;
    string left;
    string right;
};

size_t lcm(const vector<size_t>& numbers) {
    if (numbers.size() < 2) { return 0; }
    size_t lcma = lcm(numbers[0], numbers[1]);
    for (size_t k=2; k<numbers.size(); k++) {
        lcma = lcm(lcma, numbers[k]);
    }
    return lcma;
}

class Day08Map {
private:
    string instructions;
    vector<Day08Segment> segments;
    // Note: avoid this function, use proper container for graph
    size_t getIndex(string name) {
        size_t i;
        for (i=0; i<segments.size(); i++) {
            if (segments[i].name == name) break;
        }
        return i;
    }
    vector<size_t> getNodesEndingWith(char c) {
        vector<size_t> idx;
        for (size_t i=0; i<segments.size(); i++) {
            if (segments[i].name.back() == c) idx.push_back(i);
        }
        return idx;
    }
public:
    void set_instr(string instr) {
        instructions = instr;
    }
    void add_segment(string line) {
        Day08Segment s;
        s.name = line.substr(0, 3);
        s.left = line.substr(7, 3);
        s.right = line.substr(12, 3);
        segments.push_back(s);
    }
    size_t solve(bool part_one = true) {
        size_t steps = 0;
        if (part_one) {
            // find AAA
            size_t i = getIndex("AAA");
            size_t s = 0;
            while (segments[i].name != "ZZZ") {
                string target;
                if (instructions[s] == 'L') {
                    target = segments[i].left;
                } else if (instructions[s] == 'R') {
                    target = segments[i].right;
                } else {
                    cout << "Error, invalid instruction encountered" << endl;
                }
                steps++;
                if (target != segments[i].name) {
                    i = getIndex(target);
                }
                s++;
                if (s == instructions.size()) {
                    s = 0;
                }
            }
        } else {
            // Part two
            vector<size_t> init = getNodesEndingWith('A');
            vector<size_t> ends = getNodesEndingWith('Z');
            vector<size_t> p0; p0.resize(init.size());
            vector<size_t> p1; p1.resize(init.size());
            std::fill(p0.begin(), p0.end(),0);
            std::fill(p1.begin(), p1.end(),0);
            vector<size_t> state = init;
            size_t s = 0;
            bool finished = false;
            while (!finished) {
                // Step with all "state"
                for (size_t i=0; i<state.size(); i++) {
                    // Step with state[i]
                    string target;
                    if (instructions[s] == 'L') {
                        target = segments[state[i]].left;
                    } else if (instructions[s] == 'R') {
                        target = segments[state[i]].right;
                    } else {
                        cout << "Error, invalid instruction encountered" << endl;
                    }
                    size_t new_idx = state[i];
                    if (target.back() == 'Z') {
                        if (p0[i] == 0) {
                            p0[i] = steps;
                        } else if (p1[i] == 0) {
                            p1[i] = steps;
                            //cout << "Period of " << i << " is: " << p1[i]-p0[i] << endl;
                        } else {
                            p0[i] = p1[i];
                            p1[i] = steps;
                            //cout << "Period of " << i << " is: " << p1[i]-p0[i] << endl;
                        }
                    }
                    if (target != segments[state[i]].name) {
                        new_idx = getIndex(target);
                    }
                    state[i] = new_idx;
                }
                // Advance steps counter and s
                steps++;
                s++;
                if (s == instructions.size()) { s = 0; }
                // Exit loop if all periods are found
                bool check = true;
                for (size_t& p : p1) {
                    if (p == 0) check = false;
                }
                finished = check;
            } // end while
            vector<size_t> periods;
            for (size_t i=0; i<p1.size(); i++) {
                periods.push_back(p1[i]-p0[i]);
            }
            steps = lcm(periods);
        }
        return steps;
    }
};

Day08::Day08(const string& inputpath) : path(inputpath) { }

size_t Day08::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t steps = 0;
    Day08Map map;
    if (infile.is_open()) {
        getline(infile, line);
        map.set_instr(line);
        getline(infile, line);
        while (getline(infile, line)) {
            map.add_segment(line);
        }
    }
    steps = map.solve(part_one);
    return steps;
}

int main() {
    //Day08 day("test08.txt");
    //Day08 day("test08b.txt");
    //Day08 day("test08c.txt");
    Day08 day("day08.txt");
    //cout << "Day08 Part one: " << day.solve() << endl; // 20221
    cout << "Day08 Part two: " << day.solve(false) << endl;
    return 0;
}