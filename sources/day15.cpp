#include "day15.h"

/**
 * Holiday ASCII String Helper algorithm
 *  start with a current value of 0. Then, for each character in the string starting from the beginning:
 *   - Determine the ASCII code for the current character of the string.
 *   - Increase the current value by the ASCII code you just determined.
 *   - Set the current value to itself multiplied by 17.
 *   - Set the current value to the remainder of dividing itself by 256.
 */
size_t HASH(const string& s) {
    size_t v = 0;
    for (const char c : s) {
        v += static_cast<size_t>(c);
        v *= 17;
        v = (v % 256);
    }
    return v;
}

void operate(vector<vector<pair<string, int>>>& boxes, string command) {
    string label;
    size_t value;
    size_t b;
    if (contains_char(command, '-')) {
        // Remove
        command.pop_back();
        label = command;
        b = HASH(label);
        for (auto it = boxes[b].begin(); it < boxes[b].end(); it++) {
            if ((*it).first == label) {
                boxes[b].erase(it);
                break;
            }
        }
    } else if (contains_char(command, '=')) {
        vector<string> parts = split(command, '=');
        label = parts[0];
        value = stoll(parts[1]);
        b = HASH(label);
        bool exists = false;
        for (pair<string, int>& slot : boxes[b]) {
            if (slot.first == label) {
                slot.second = value;
                exists = true;
                break;
            }
        }
        if (!exists) {
            boxes[b].emplace_back(label, value);
        }
    }
}

Day15::Day15(const string& inputpath) : path(inputpath) { }

int Day15::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t total = 0;

    vector<string> parts;
    vector<vector<pair<string, int>>> boxes;
    if (infile.is_open()) {
        getline(infile, line);
        parts = split(line, ',');
    }
    if (part_one) {
        for (const string& s : parts) {
            total += HASH(s);
        }
    } else {
        // Part two
        boxes.resize(256);
        for (const string& s : parts) {
            operate(boxes, s);
        }
        // Calculate focusing power
        size_t fpower = 0;
        // One plus the box number of the lens in question.
        // The slot number of the lens within the box: 1 for the first lens, 2 for the second lens, and so on.
        // The focal length of the lens.
        for (size_t b = 0; b<256; b++) {
            size_t slot = 1;
            for (auto& p : boxes[b]) {
                fpower += (b+1)*slot*p.second;
                slot++;
            }
        }
        total = fpower;
    }
    return total;
}

int main() {
    //Day15 day("test15.txt");
    Day15 day("day15.txt");
    cout << "Day15 Part one: " << day.solve() << endl;
    cout << "Day15 Part two: " << day.solve(false) << endl;
    return 0;
}