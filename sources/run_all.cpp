#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"

#include <chrono>
#include <iomanip>
using namespace std::chrono;

template <class Day>
tuple<double,double> benchmark_day(const Day& day) {
    double dur1, dur2;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    day.solve();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    dur1 = duration_cast<duration<double>>(t2 - t1).count()*1000.0;

    t1 = high_resolution_clock::now();
    day.solve(false);
    t2 = high_resolution_clock::now();
    dur2 = duration_cast<duration<double>>(t2 - t1).count()*1000.0;

    return make_tuple(dur1, dur2);
}

int main() {

    vector<string> day_titles = {
        "Trebuchet?!",
        "Cube Conundrum",
        "Gear Ratios",
        "Scratchcards",
        //"If You Give A Seed A Fertilizer",
        "Wait For It"
    };

    vector<tuple<double, double>> times;
    times.push_back(benchmark_day(Day01("day01.txt")));
    times.push_back(benchmark_day(Day02("day02.txt")));
    times.push_back(benchmark_day(Day03("day03.txt")));
    times.push_back(benchmark_day(Day04("day04.txt")));
    //times.push_back(benchmark_day(Day05("day05.txt")));
    times.push_back(benchmark_day(Day06("day06.txt")));

    // Print result to cout
    cout << endl << endl;
    cout << "Task  \t\tP1 [ms]\t\tP2 [ms]\n";
    cout << "------\t\t-------\t\t-------\n";
    cout << setprecision(3) << fixed;
    for (size_t i=0; i<day_titles.size(); i++) {
        cout << day_titles[i] << "\t\t" << get<0>(times[i]) << "\t\t" << get<1>(times[i]) << '\n';
    }
    flush(cout);

    // Also print to readme.md
    ofstream out("../README.md");
    out << "# aoc23\n";
    out << "Advent of Code 2023 in C++\n";
    out << "## Introduction\n";
    out << "My goal for this year is to provide tests (using puzzle samples) and try to practice modern C++ language and library features wherever possible\n";
    out << "## Computation times (no optimizations, both parts run separately and parse the input file).\n";
    out << "Processor: Intel(R) Core(TM) i7-12700H, single thread unless indicated\n";
    out << endl;
    out << "Day | Part One [ms] | Part Two [ms]\n";
    out << "--- | ---: | ---:\n";
    out << setprecision(3) << fixed;
    double time_sum = 0;
    for (size_t i=0; i<day_titles.size(); i++) {
        out << "Day " << to_string(i+1) << ": " << day_titles[i] << " | " << get<0>(times[i]) << " | " << get<1>(times[i]) << '\n';
        time_sum += get<0>(times[i])+get<1>(times[i]);
    }
    out << endl;
    out << "Total time: " << time_sum/1000.0 << " seconds (" << time_sum << " ms)\n";
    out << endl;


    return 0;
}