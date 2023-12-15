#include <numeric>
#include "day09.h"

bool is_stable(const vector<int>& d) {
    for (const auto& v : d) {
        if (v != 0) return false;
    }
    return true;
}

bool extrapolate(const vector<int>& seq, int& ext) {
    vector<vector<int>> derivatives;
    vector<int> d;
    for (size_t i=0; i<seq.size()-1; i++) {
        d.push_back(seq[i+1]-seq[i]);
    }
    while (!is_stable(d)) {
        // Store this derivative
        derivatives.push_back(d);
        // Generate next
        vector<int> dnext;
        if (d.size() == 1) {
            cout << "Error: sequence length is not long enough to calculate derivative of necessary order!" << endl;
            return false;
        }
        for (size_t i=0; i<d.size()-1; i++) {
            dnext.push_back(d[i+1]-d[i]);
        }
        d = dnext;
    }
    int shift = 0;
    for (auto & derivative : derivatives) shift += derivative.back();
    ext = static_cast<int>(seq.back())+shift;
    /*static bool debug = true;
    if (debug) {
        for (const auto& v : seq) cout << v << " ";
        cout << "-> " << ext << endl;
        for (auto & derivative : derivatives) {
            for (const auto& v : derivative) cout << v << " ";
            cout << endl;
        }
    }*/
    return true;
}

Day09::Day09(const string& inputpath) : path(inputpath) { }

int Day09::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    vector<vector<int>> seq_list;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            vector<int> sequence;
            vector<string> num_str = split(line, ' ');
            if (!part_one) std::reverse(num_str.begin(), num_str.end());
            transform(num_str.begin(), num_str.end(), back_inserter(sequence), str_to_int64());
            seq_list.push_back(sequence);
        }
    }
    int extrapolated = 0;
    int total = 0;
    for (vector<int>& seq : seq_list) {
        extrapolate(seq, extrapolated);
        total += extrapolated;
    }
    return total;
}