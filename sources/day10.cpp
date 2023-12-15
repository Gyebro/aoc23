#include "day10.h"

enum PipeDirection {
    LU, // J
    RU, // L
    LD, // 7
    RD, // F
    HOR, // -
    VERT, // |
    NONE
};

struct corners_inside {
public:
    bool lu;
    bool ru;
    bool ld;
    bool rd;
};

class PipeNetwork {
private:
    vector<string> map;
    vector<vector<bool>> visited;
    vector<vector<size_t>> dist;
    vector<vector<corners_inside>> corners;
    pair<int, int> start;
    size_t max_steps;
    void init_states() {
        vector<size_t> d(map[0].size());
        std::fill(d.begin(), d.end(),0);
        dist.resize(map.size());
        std::fill(dist.begin(), dist.end(),d);
        vector<bool> v(map[0].size());
        std::fill(v.begin(), v.end(),false);
        visited.resize(map.size());
        std::fill(visited.begin(), visited.end(),v);
    }
    bool is_visited(const pair<int, int>& p) {
        return visited[p.first][p.second];
    }
    void set_visited(const pair<int, int>& p) {
        visited[p.first][p.second] = true;
    }
    size_t distance(const pair<int, int>& p) {
        return dist[p.first][p.second];
    }
    void set_distance(const pair<int, int>& p, const size_t& d) {
        dist[p.first][p.second] = d;
    }
    vector<pair<int, int>> get_neighbours(const pair<int, int>& p) {
        vector<pair<int, int>> n;
        switch (map[p.first][p.second]) {
            case '.':
                break;
            case 'J':
                if (p.first > 0) n.emplace_back(p.first-1, p.second);
                if (p.second > 0) n.emplace_back(p.first, p.second-1);
                break;
            case 'L':
                if (p.first > 0) n.emplace_back(p.first-1, p.second);
                if (p.second < map[0].size()) n.emplace_back(p.first, p.second+1);
                break;
            case '7':
                if (p.first < map.size()) n.emplace_back(p.first+1, p.second);
                if (p.second > 0) n.emplace_back(p.first, p.second-1);
                break;
            case 'F':
                if (p.first < map.size()) n.emplace_back(p.first+1, p.second);
                if (p.second < map[0].size()) n.emplace_back(p.first, p.second+1);
                break;
            case '|':
                if (p.first > 0) n.emplace_back(p.first-1, p.second);
                if (p.first < map.size()) n.emplace_back(p.first+1, p.second);
                break;
            case '-':
                if (p.second > 0) n.emplace_back(p.first, p.second-1);
                if (p.second < map[0].size()) n.emplace_back(p.first, p.second+1);
                break;
            case 'S':
                cout << "Reached 'S', which is unexpected!";
                break;

        }
        return n;
    }
    void print_visited_map() {
        for (const vector<bool>& v : visited) {
            for (const bool& b : v) {
                cout << (b ? "X" : ".");
            }
            cout << endl;
        }
    }
    void print_distance_map() {
        for (const vector<size_t>& v : dist) {
            for (const size_t& b : v) {
                cout << b;
            }
            cout << endl;
        }
    }
public:
    void add_line(const string& line) {
        for (size_t j=0; j<line.size(); j++) {
            if (line[j] == 'S') start = make_pair(map.size(),j);
        }
        map.push_back(line);
    }
    void do_dfs() {
        init_states();
        vector<pair<int, int>> st;
        // Probe 4 neighbours of S
        vector<pair<int, int>> nl = get_neighbours(make_pair(start.first, start.second-1));
        vector<pair<int, int>> nr = get_neighbours(make_pair(start.first, start.second+1));
        vector<pair<int, int>> nu = get_neighbours(make_pair(start.first-1, start.second));
        vector<pair<int, int>> nd = get_neighbours(make_pair(start.first+1, start.second));
        set_visited(start);
        bool l = false, r = false, d = false, u = false;
        if (contains(nl,start)) {
            //cout << "Starting direction LEFT added\n";
            st.emplace_back(start.first, start.second-1); l = true;
        }
        if (contains(nr,start)) {
            //cout << "Starting direction RIGHT added\n";
            st.emplace_back(start.first, start.second+1); r = true;
        }
        if (contains(nu,start)) {
            //cout << "Starting direction UP added\n";
            st.emplace_back(start.first-1, start.second); u = true;
        }
        if (contains(nd,start)) {
            //cout << "Starting direction DOWN added\n";
            st.emplace_back(start.first+1, start.second); d = true;
        }
        // Replace S with a proper pipe tile
        char S;
        if (l) {
            if (u) S = 'J';
            else if (d) S = '7';
            else if (r) S = '-';
            else cout << "Error: impossible starting pipe tile" << endl;
        } else if (r) {
            if (u) S = 'L';
            else if (d) S = 'F';
            else cout << "Error: impossible starting pipe tile" << endl;
        } else if (u) {
            if (d) S = '|';
            else cout << "Error: impossible starting pipe tile" << endl;
        }
        map[start.first][start.second] = S;
        dfs(st, 0);
    }
    void dfs(vector<pair<int, int>>& locs, size_t steps) {
        vector<pair<int, int>> new_locs;
        for (const pair<int, int>& p : locs) {
            set_visited(p);
            set_distance(p, steps+1);
            vector<pair<int,int>> n = get_neighbours(p);
            size_t count = 0;
            for (const pair<int,int>& p : n) {
                if (!is_visited(p)) {
                    new_locs.push_back(p);
                    count++;
                }
            }
            if (count == 0) {
                //cout << "Path terminated\n";
            } else if (count > 1) {
                cout << "Error: more than two endpoints found for pipe!\n";
            }
        }
        locs = new_locs;
        //print_visited_map();
        //print_distance_map();
        max_steps = steps+1;
        if (locs.size() > 0) {
            return dfs(locs, steps+1);
        } else {
            return;
        }
    }
    size_t get_max_steps() const {
        return max_steps;
    }
    void print_loop() {
        set_distance(start, 1);
        cout << endl;
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[0].size(); j++) {
                cout << (dist[i][j] > 0 ? map[i][j] : '.');
            }
            cout << endl;
        }
    }
    size_t analyze_bounds() {
        size_t inside = 0;
        // Create a special element to track borders for each cell
        corners_inside outside{false, false, false, false};
        vector<corners_inside> crow;
        crow.resize(map[0].size());
        std::fill(crow.begin(), crow.end(), outside);
        corners.resize(map.size());
        std::fill(corners.begin(), corners.end(), crow);
        set_distance(start, 1);
        // Clean up map: replace non-loop pipes with '.'
        for (size_t i=0; i<map.size(); i++) {
            for (size_t j=0; j<map[0].size(); j++) {
                if (dist[i][j]==0) map[i][j] = '.';
            }
        }
        // Start scanning lines, assume that -1-th row is outside
        for (size_t i=1; i<map.size(); i++) {
            corners_inside up;
            corners_inside left;
            for (size_t j=0; j<map[0].size(); j++) {
                if (j == 0) { left = outside; }
                else { left = corners[i][j-1]; }
                up = corners[i-1][j];
                corners_inside thistile;
                // TODO: Check using upper neighbour
                switch(map[i][j]) {
                    case '.': // Horizontal inherit
                        thistile.lu = left.ru;
                        thistile.ld = left.rd;
                        thistile.ru = thistile.lu;
                        thistile.rd = thistile.ld;
                        break;
                    case '|': // Horizontal NOT
                        thistile.lu = left.ru;
                        thistile.ld = left.rd;
                        thistile.ru = !thistile.lu;
                        thistile.rd = !thistile.ld;
                        break;
                    case '-': // Horizontal inherit or Vertical NOT
                        thistile.lu = left.ru;
                        thistile.ld = left.rd;
                        thistile.ru = thistile.lu;
                        thistile.rd = thistile.ld;
                        break;
                    case 'F': // Up: Horizontal inherit, Down: Horizontal NOT
                    case '7':
                        thistile.lu = left.ru;
                        thistile.ld = left.rd;
                        thistile.ru = thistile.lu;
                        thistile.rd = !thistile.ld;
                        break;
                    case 'L': // Down: Horizontal inherit, Up: Horizontal NOT
                    case 'J':
                        thistile.lu = left.ru;
                        thistile.ld = left.rd;
                        thistile.ru = !thistile.lu;
                        thistile.rd = thistile.ld;
                        break;
                    default:
                        cout << "Error, this pipe tile should not appear here" << endl;
                }
                corners[i][j] = thistile;
                if ((map[i][j] == '.') && thistile.lu && thistile.ru && thistile.ld && thistile.rd) inside++;
            }
        }
        return inside;
    }
};

Day10::Day10(const string& inputpath) : path(inputpath) { }

int Day10::solve(bool part_one) const {
    string line;
    ifstream infile(path);

    PipeNetwork pn;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            pn.add_line(line);
        }
    }
    pn.do_dfs();
    if (part_one) {
        return pn.get_max_steps();
    } else {
        return pn.analyze_bounds();
    }

}

int main() {
    //Day10 day("test10.txt");
    //Day10 day("test10b.txt");
    Day10 day("day10.txt");
    cout << "Day10 Part one: " << day.solve() << endl;
    cout << "Day10 Part two: " << day.solve(false) << endl;
    return 0;
}
