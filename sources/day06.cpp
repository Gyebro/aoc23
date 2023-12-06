#include "day06.h"
#include "math.h"

Day06::Day06(const string& inputpath) : path(inputpath) { }

class Day06Race {
public:
    Day06Race(size_t time, size_t record) : time(time), record(record) {}
    size_t time;
    size_t record;
    size_t dist(size_t charge) const {
        if (charge > time) return 0;
        else return (charge*(time-charge));
    }
    size_t getMultiplicityNaive() const {
        size_t win = 0;
        for (size_t chg = 1; chg < time; chg++) {
            if (dist(chg) > record) win++;
        }
        return win;
    }
    size_t getMultiplicity() const {
        /**
         * The curve describing distance is a 2nd order polynomial (parabola, opening downwards)
         *  c*(t-c) (where c is the charge-up time and t is the total time)
         * the condition of beating the record is
         *  c*(t-c)>r, that is c*(t-c)-r>0
         * The 2nd order polynomial -c^2 + c*t - r = 0 has two roots (c0 and c1) and
         * the number of winning options are between these two
         *  c1-c0 = sqrt(t^2-4*r)
         * in order to get integer domain right, the roots are calculated separately and perturbed
         *  with a small value to avoid equality (ensure d>r instead of d>=r)
         */
         double t = static_cast<double>(time);
         double r = static_cast<double>(record);
         double sts4r = sqrt(t*t-4.0*r);
         double c0 = (t-sts4r)/2.0+0.01;
         double c1 = (t+sts4r)/2.0-0.01;
         size_t c0int = static_cast<size_t>(ceil(c0));
         size_t c1int = static_cast<size_t>(floor(c1));
         return c1int-c0int+1; // Interval length between two roots in integer domain
    }
};

int Day06::solve(bool part_one) const {
    ifstream infile(path);
    vector<Day06Race> races;
    if (infile.is_open()) {
        string time_list;
        string dist_list;
        getline(infile, time_list);
        getline(infile, dist_list);
        vector<size_t> times;
        vector<size_t> dist_records;
        if (part_one) {
            vector<string> time_strings = split(sanitize_spaces(split(time_list, ':')[1]), ' ');
            vector<string> dist_strings = split(sanitize_spaces(split(dist_list, ':')[1]), ' ');
            std::transform(time_strings.begin(), time_strings.end(), back_inserter(times), str_to_ul());
            std::transform(dist_strings.begin(), dist_strings.end(), back_inserter(dist_records), str_to_ul());
        } else {
            // Part two:
            string time = replace_substring(sanitize_spaces(split(time_list, ':')[1])," ","");
            string dist = replace_substring(sanitize_spaces(split(dist_list, ':')[1])," ","");
            times.push_back(stoull(time));
            dist_records.push_back(stoull(dist));
        }
        for (size_t i=0; i<times.size(); i++) {
            races.emplace_back(times[i], dist_records[i]);
        }

    }
    size_t race_winning_multiplicity = 1;
    for (Day06Race& r : races) {
        race_winning_multiplicity *= r.getMultiplicity();
    }
    return race_winning_multiplicity;
}
