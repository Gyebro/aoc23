#include <numeric>
#include "day03.h"

bool is_digit(const char c) {
    return contains_char("0123456789", c);
}

bool is_symbol(const char c) {
    if (c == '.') {
        return false;
    } else if (is_digit(c)) {
        return false;
    }
    return true;
}

class Day03Schematic {
private:
    vector<string> map;
    vector<vector<bool>> is_part_number;
    vector<int> part_numbers;
    vector<vector<int>> is_gear;
    vector<vector<int>> gear_numbers;
    size_t width, height;
    void set_part_number(size_t i, size_t j) {
        if (i > 0) {
            is_part_number[i-1][j] = true;
            if (j > 0) is_part_number[i-1][j-1] = true;
            if (j < width-1) is_part_number[i-1][j+1] = true;
        }
        if (j > 0) is_part_number[i][j-1] = true;
        if (j < width-1) is_part_number[i][j+1] = true;
        if (i < height-1) {
            is_part_number[i+1][j] = true;
            if (j > 0) is_part_number[i+1][j-1] = true;
            if (j < width-1) is_part_number[i+1][j+1] = true;
        }
    }
    void set_gear_number(size_t i, size_t j, int g) {
        if (i > 0) {
            is_gear[i-1][j] = g;
            if (j > 0) is_gear[i-1][j-1] = g;
            if (j < width-1) is_gear[i-1][j+1] = g;
        }
        if (j > 0) is_gear[i][j-1] = g;
        is_gear[i][j] = g;
        if (j < width-1) is_gear[i][j+1] = g;
        if (i < height-1) {
            is_gear[i+1][j] = g;
            if (j > 0) is_gear[i+1][j-1] = g;
            if (j < width-1) is_gear[i+1][j+1] = g;
        }
    }
    void process_map() {
        // Find symbols and mark map cells as 'is_part_number', then collect part numbers
        // Initialize is_part_number
        vector<bool> bline;
        bline.resize(width);
        std::fill(bline.begin(), bline.end(), false);
        is_part_number.resize(height);
        std::fill(is_part_number.begin(), is_part_number.end(), bline);
        // Scan map and mark part_number locations
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                if (is_symbol(map[i][j])) {
                    set_part_number(i, j);
                }
            }
        }
        // Scan for numbers
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                if (is_digit(map[i][j])) {
                    size_t jstart = j;
                    size_t j0 = j;
                    while(is_digit(map[i][j0])) {
                        j0++;
                    }
                    size_t jend = j0;
                    // Number found
                    //cout << "Number found: " << map[i].substr(jstart,jend-jstart) << endl;
                    // Check 'is_part_number'
                    bool part_num = false;
                    for (size_t p = jstart; p < jend; p++) {
                        if (is_part_number[i][p]) part_num = true;
                    }
                    //if (part_num) cout << "Part number found: " << map[i].substr(jstart,jend-jstart) << endl;
                    if (part_num) part_numbers.push_back(stoi(map[i].substr(jstart,jend-jstart)));
                    j = jend; // advance internal for loop
                }
            }
        }
    }
    void process_gears() {
        // Find gears and mark map with their unique ID, then scan for numbers and store them in gear_numbers
        // Initialize is_gear with -1
        vector<int> gline;
        gline.resize(width);
        std::fill(gline.begin(), gline.end(), -1);
        is_gear.resize(height);
        std::fill(is_gear.begin(), is_gear.end(), gline);
        // Scan map and mark gear locations, NOTE: currently only 1 gear ID is allowed for each map tile
        int g = 0;
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                if (map[i][j] == '*') {
                    set_gear_number(i, j, g);
                    g++;
                }
            }
        }
        gear_numbers.resize(g);
        // Scan for gear-related-numbers
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                if (is_digit(map[i][j])) {
                    size_t jstart = j;
                    size_t j0 = j;
                    while(is_digit(map[i][j0])) {
                        j0++;
                    }
                    size_t jend = j0;
                    // Number found
                    int num = stoi(map[i].substr(jstart,jend-jstart));
                    vector<int> gear_assignments; // Keep track of which gear this number has been assigned to
                    for (size_t p = jstart; p < jend; p++) {
                        if (is_gear[i][p] > -1) {
                            int gp = is_gear[i][p];
                            if (!contains(gear_assignments, gp)) {
                                gear_numbers[gp].push_back(num);
                                gear_assignments.push_back(gp);
                            }
                        }
                    }
                    j = jend; // advance internal for loop
                }
            }
        }
    }
public:
    Day03Schematic(ifstream& infile, bool part_one = true) {
        string line;
        if (infile.is_open()) {
            while (getline(infile, line)) {
                map.push_back(line);
            }
            infile.close();
        }
        height = map.size();
        width = map[0].size();
        if (part_one) {
            process_map();
        } else {
            process_gears();
        }
    }
    void printIsPN() {
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                cout << (is_part_number[i][j] ? "#" : ".");
            }
            cout << endl;
        }
    }
    void printIsGear() {
        for (size_t i=0; i<height; i++) {
            for (size_t j=0; j<width; j++) {
                if (is_gear[i][j] > -1) cout << is_gear[i][j];
                else cout << ".";
            }
            cout << endl;
        }
    }
    int getPartNumSum() {
        return accumulate(part_numbers.begin(), part_numbers.end(), 0);
    }
    size_t getGearRatioSum() {
        size_t sum = 0;
        size_t gears = 0;
        size_t gi = 0;
        bool debug = false;
        for (const vector<int>& gn : gear_numbers) {
            if (gn.size() == 2) {
                if (debug) cout << "Gear found with ratio " << gn[0] << " x " << gn[1] << endl;
                sum += gn[0]*gn[1];
                gears++;
            } else {
                // Print vicinity of this gears
                if (debug) {
                    for (size_t i = 0; i < height; i++) {
                        bool end_line = false;
                        for (size_t j = 0; j < width; j++) {
                            if (is_gear[i][j] == gi) {
                                cout << map[i][j];
                                end_line = true;
                            }
                        }
                        if (end_line) cout << endl;
                    }
                    cout << "^^^ Map around non-gear star: " << gi << endl;
                }
            }
            gi++;
        }
        return sum;
    }
};

Day03::Day03(const string& inputpath) : path(inputpath) { }

int Day03::solve(bool part_one) const {
    ifstream infile(path);
    Day03Schematic schematic(infile, part_one);
    if (part_one) {
        return schematic.getPartNumSum();
    } else {
        return schematic.getGearRatioSum();
    }

}