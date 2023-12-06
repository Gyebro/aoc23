#include <numeric>
#include "day05.h"

Day05::Day05(const string& inputpath) : path(inputpath) { }

struct MapInterval {
    size_t destination;
    size_t source;
    size_t range_length;
};

class Day05Map {
public:
    vector<MapInterval> intervals;
    size_t apply(const size_t value) {
        for (const MapInterval& i : intervals) {
            if ((value >= i.source && value < (i.source+i.range_length))) {
                return (i.destination + value - i.source);
            }
        }
        return value;
    }
};

const string map_a_header = "seed-to-soil";
const string map_b_header = "soil-to-fertilizer";
const string map_c_header = "fertilizer-to-water";
const string map_d_header = "water-to-light";
const string map_e_header = "light-to-temperature";
const string map_f_header = "temperature-to-humidity";
const string map_g_header = "humidity-to-location";

int Day05::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t sum = 0;
    // Note: for simplicity, use letters
    // [a, b, c, d, e, f, g, h]
    // [seed, soil, fertilizer, water, light, temperature, humidity, location]
    vector<Day05Map> maps;
    maps.resize(7);
    vector<size_t> seeds;
    if (infile.is_open()) {
        int state = -1;
        getline(infile, line);
        // Parse seeds
        string seeds_str = trim_spaces(split(line, ':')[1]);
        vector<string> seeds_s = split(seeds_str, ' ');
        std::transform(seeds_s.begin(), seeds_s.end(), back_inserter(seeds), str_to_ul());
        while (getline(infile, line)) {
            if (line.find(map_a_header) == 0) {
                state = 0;
            } else if (line.find(map_b_header) == 0) {
                state = 1;
            } else if (line.find(map_c_header) == 0) {
                state = 2;
            } else if (line.find(map_d_header) == 0) {
                state = 3;
            } else if (line.find(map_e_header) == 0) {
                state = 4;
            } else if (line.find(map_f_header) == 0) {
                state = 5;
            } else if (line.find(map_g_header) == 0) {
                state = 6;
            } else if (!line.empty()) {
                vector<string> numbers = split(line, ' ');
                MapInterval inter;
                inter.destination = stoul(numbers[0]);
                inter.source = stoul(numbers[1]);
                inter.range_length = stoul(numbers[2]);
                maps[state].intervals.push_back(inter);
            }
        }
        infile.close();
    }
    vector<size_t> transformed;
    if (part_one) {
        for (int m = 0; m < maps.size(); m++) {
            transformed.clear();
            for (const size_t& s : seeds) {
                size_t t = maps[m].apply(s);
                transformed.push_back(t);
            }
            /*for (const size_t& v : transformed) {
                cout << v << " ";
            }
            cout << endl;*/
            seeds = transformed;
        }
    }
    return *min_element(seeds.begin(), seeds.end());
}

int main() {
    //Day05 day05("test05.txt");
    Day05 day05("day05.txt");
    cout << "Part one: " << day05.solve() << endl;
    return 0;
}