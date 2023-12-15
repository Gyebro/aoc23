#include <numeric>
#include <limits>
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
    size_t apply(const size_t value) const {
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

size_t get_lowest_location(const vector<Day05Map>& maps, const MapInterval& seed_interval) {
    size_t lowest = numeric_limits<size_t>::max();
    for (size_t s = seed_interval.source; s < seed_interval.source+seed_interval.range_length; s++) {
        size_t loc = s;
        for (const auto & map : maps) {
            loc = map.apply(loc);
        }
        if (loc < lowest) {
            lowest = loc;
        }
    }
    return lowest;
}

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
    size_t min_loc = 0;
    if (part_one) {
        vector<size_t> transformed;
        for (int m = 0; m < maps.size(); m++) {
            transformed.clear();
            for (const size_t& s : seeds) {
                size_t t = maps[m].apply(s);
                transformed.push_back(t);
            }
            seeds = transformed;
        }
        min_loc = *min_element(transformed.begin(), transformed.end());
    } else {
        // First guess for a working algorithm:
        //  find the lowest 2-3 intervals of the last map (including the identity map of range 0-N) and
        //  work backwards. Then check intersection with seed ranges
        // But first: brute force this

        // Gather seed intervals
        vector<MapInterval> seed_ints;
        for (size_t i=0; i<seeds.size(); i+=2) {
            MapInterval inter;
            inter.source = seeds[i];
            inter.range_length = seeds[i + 1]/2;
            seed_ints.push_back(inter);
            inter.source = seeds[i]+seeds[i + 1]/2-1;
            inter.range_length = seeds[i + 1]/2;
            seed_ints.push_back(inter);
        }
        vector<size_t> lowest_in_blocks;
#pragma omp parallel
        {
            vector<size_t> lowest_private;
#pragma omp for nowait
            for (const MapInterval& inter : seed_ints) {
                lowest_private.push_back(get_lowest_location(maps, inter));
            }
#pragma omp critical
            lowest_in_blocks.insert(lowest_in_blocks.end(), lowest_private.begin(), lowest_private.end());
        }
        min_loc = *min_element(lowest_in_blocks.begin(), lowest_in_blocks.end());
    }
    return min_loc;
}