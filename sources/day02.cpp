#include "day02.h"

enum Day02Color {
    Red,
    Green,
    Blue
};

class Day02Game {
private:
    int id;
    int largestDraw[3];
    void parseDraw(const string& drawString) {
        vector<string> elements = split(drawString, ',');
        for (const string& e : elements) {
            vector<string> parts = split(trim_spaces(e), ' ');
            int count = stoi(parts[0]);
            string color = parts[1];
            Day02Color c;
            bool ok = true;
            if (color == "red") {
                c = Red;
            } else if (color == "green") {
                c = Green;
            } else if (color == "blue") {
                c = Blue;
            } else {
                ok = false;
                cout << "Error: unknown ball colour in Game with ID '" << id << "'" << endl;
            };
            if (ok) {
                if (largestDraw[c] < count) largestDraw[c] = count;
            }
        }
    }
public:
    Day02Game() {
        largestDraw[Red] = 0;
        largestDraw[Green] = 0;
        largestDraw[Blue] = 0;
    }
    void parse(const string& line) {
        vector<string> parts = split(line, ':');
        string header = parts[0];
        string drawsString = parts[1];
        string idString = split(header, ' ')[1];
        id = stoi(idString);
        vector<string> draws = split(drawsString, ';');
        for (const string& aDraw : draws) {
            parseDraw(aDraw);
        }
    }
    bool isPossible() const {
        return (largestDraw[Red] <= 12) && (largestDraw[Green] <= 13) && (largestDraw[Blue] <= 14);
    }
    int getId() const {
        return id;
    }
    int getPower() const {
        return largestDraw[Red]*largestDraw[Green]*largestDraw[Blue];
    }
};

Day02::Day02(const string& inputpath) : path(inputpath) { }

int Day02::solve(bool part_one) const {
    string line;
    ifstream infile(path);
    vector<Day02Game> games;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            Day02Game game;
            game.parse(line);
            games.push_back(game);
        }
        infile.close();
    }
    int sum = 0;
    if (part_one) {
        for (const Day02Game &g: games) {
            if (g.isPossible()) {
                sum += g.getId();
            }
        }
    } else {
        for (const Day02Game &g: games) {
            sum += g.getPower();
        }
    }
    return sum;
}