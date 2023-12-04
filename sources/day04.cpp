#include "day04.h"
#include <math.h>
#include <numeric>

struct str_to_int {
    int operator()(const string& s) {
        return stoi(s);
    }
};

class Day04Card {
private:
    vector<int> winners;
    vector<int> numbers;
public:
    Day04Card(const string& line) {
        vector<string> parts = split(line, ':');
        vector<string> num_strs = split(parts[1], '|');
        string w_strs = sanitize_spaces(num_strs[0]);
        string n_strs = sanitize_spaces(num_strs[1]);
        vector<string> winners_str = split(w_strs, ' ');
        vector<string> numbers_str = split(n_strs, ' ');
        std::transform(winners_str.begin(), winners_str.end(), back_inserter(winners), str_to_int());
        std::transform(numbers_str.begin(), numbers_str.end(), back_inserter(numbers), str_to_int());
    }
    size_t power() const {
        size_t power = 0;
        for (const int& w : winners) {
            for (const int& n : numbers) {
                if (n == w) power++;
            }
        }
        return power;
    }
    size_t score() const {
        size_t pw = power();
        if (pw == 0) { return 0; }
        else { return static_cast<int>(std::pow(2.0, pw-1)); }
    }
};

Day04::Day04(const string& inputpath) : path(inputpath) { }

int Day04::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t sum = 0;
    vector<size_t> card_powers;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            Day04Card card(line);
            if (part_one) {
                sum += card.score();
            } else {
                card_powers.push_back(card.power());
            }
        }
        infile.close();
    }
    if (!part_one) {
        // Resolve card copies
        vector<size_t> copies;
        size_t cards = card_powers.size();
        copies.resize(cards);
        std::fill(copies.begin(), copies.end(),1);
        for (size_t i=0; i<cards-1; i++) {
            size_t pow_i = card_powers[i];
            for (size_t k=i+1; k<min(i+pow_i+1,cards); k++) {
                copies[k] += copies[i];
            }
        }
        sum = accumulate(copies.begin(), copies.end(), 0);
    }
    return sum;
}