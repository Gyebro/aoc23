#include "day07.h"

enum Day07Type {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOf,
    FullHouse,
    FourOf,
    FiveOf
};

static const int basepow0 = 1;
static const int basepow1 = 14;
static const int basepow2 = 196;
static const int basepow3 = 2744;
static const int basepow4 = 38416;
static const vector<int> base({basepow4,basepow3,basepow2,basepow1,basepow0});

int Day07Value(const char c) {
    switch (c) {
        case '2':
            return 1;
        case '3':
            return 2;
        case '4':
            return 3;
        case '5':
            return 4;
        case '6':
            return 5;
        case '7':
            return 6;
        case '8':
            return 7;
        case '9':
            return 8;
        case 'T':
            return 9;
        case 'J':
            return 10;
        case 'Q':
            return 11;
        case 'K':
            return 12;
        case 'A':
            return 13;
        default:
            return 0;
    }
}

int Day07ValueB(const char c) {
    switch (c) {
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'T':
            return 10;
        case 'J':
            return 1;
        case 'Q':
            return 11;
        case 'K':
            return 12;
        case 'A':
            return 13;
        default:
            return 0;
    }
}

class Day07Hand {
private:
    vector<char> cards;
    size_t bid;
    Day07Type type;
    int(*comparison)(char);
public:
    Day07Hand(const string& s, int(*cardvalue_func)(char)) {
        vector<string> parts = split(s, ' ');
        bid = stoul(parts[1]);
        string cards_str = parts[0];
        cards = std::vector<char>(cards_str.begin(), cards_str.end());
        comparison = cardvalue_func;
    }
    int getTypeValue() const {
        return static_cast<int>(type);
    }
    int getHighCardValue() const {
        int value = 0;
        for (size_t i=0; i<5; i++) value+=base[i]*comparison(cards[i]);
        return value;
    }
    void interpret(bool part_one = true) {
        // Find out hand type
        vector<size_t> counts;
        counts.resize(13);
        fill(counts.begin(), counts.end(), 0);
        int cFirst, cSecond;
        if (part_one) {
            for (const char &c: cards) {
                counts[comparison(c) - 1]++;
            }
            sort(counts.begin(), counts.end(), greater<>());
            cFirst = counts[0];
            cSecond = counts[1];
        } else {
            /*for (const char &c: cards) {
                counts[comparison(c) - 1]++;
            }
            sort(counts.begin(), counts.end(), greater<>());
            int cFirst0 = counts[0];
            int cSecond0 = counts[1];
            fill(counts.begin(), counts.end(), 0);*/
            // Count J-s
            int cJ = 0;
            vector<char> lCards = cards;
            for (char& c : lCards) {
                if (c == 'J') {
                    cJ++;
                    c = '0'; // Replace card with a null-value
                }
            }
            for (const char &c: lCards) {
                if (comparison(c) > 0) {
                    counts[comparison(c) - 1]++;
                }
            }
            sort(counts.begin(), counts.end(), greater<>());
            cFirst = counts[0]+cJ;
            cSecond = counts[1];
            /*if (cJ != 0) {
                cout << "Joker applied, J=" << cJ << ", card is " << cFirst << "-" << cSecond << " instead of " << cFirst0 << "-" << cSecond0 << endl;
            } */
        }
        if (cFirst == 5) {
            type = FiveOf;
        } else if (cFirst == 4) {
            type = FourOf;
        } else if ((cFirst == 3) && (cSecond == 2)) {
            type = FullHouse;
        } else if (cFirst == 3) {
            type = ThreeOf;
        } else if ((cFirst == 2) && (cSecond == 2)) {
            type = TwoPairs;
        } else if (cFirst == 2) {
            type = OnePair;
        } else {
            if (cFirst != 1) cout << "Error during hand interpretation" << endl;
            type = HighCard;
        }
    }
    bool operator<(const Day07Hand &rhs) const {
        int lvalue = getTypeValue();
        int rvalue = rhs.getTypeValue();
        if (lvalue != rvalue) {
            return lvalue < rvalue;
        } else {
            int lhighcard = getHighCardValue();
            int rhighcard = rhs.getHighCardValue();
            return lhighcard < rhighcard;
        }
    }
    size_t getBid() const {
        return bid;
    }
};

Day07::Day07(const string& inputpath) : path(inputpath) { }

int Day07::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    size_t sum = 0;
    vector<Day07Hand> hands;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (part_one) {
                hands.emplace_back(line, &Day07Value);
            } else {
                hands.emplace_back(line, &Day07ValueB);
            }
        }
    }
    for (Day07Hand& h : hands) {
        h.interpret(part_one);
    }
    sort(hands.begin(), hands.end());
    for (size_t r=0; r < hands.size(); r++) {
        sum += (r + 1) * hands[r].getBid();
    }
    return sum;
}