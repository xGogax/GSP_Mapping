#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include "Skelet/BusStop.h"

#include <cmath>
#include <queue>

class Functionality {
public:
    Functionality() : busStops(BusStop::getBusStops()) {
        for (auto& pair : busStops) {
            const BusStop& stop = pair.second;
            for (const auto& line : stop.getBusLines()) {
                if (std::find(lines.begin(), lines.end(), line) == lines.end()) {
                    lines.push_back(line);
                }
            }
        }
        sortLines(lines);
    }

    unordered_set<string> getCommonLines(const string& line) const;
    bool passesThroughInSameDirection(const string& line, int stop1, int stop2) const;
    vector<string> getMostCommonLines(const string& line) const;
    pair<int,string> findNearestStop(double lat, double lon, const string& line = "") const;
    void countCommonStops(int minCommon) const;
    vector<string> getLinesForStop(int stopID, bool print = true) const;
    vector<pair<int,string>> getNextStops(int stopID, bool print = true) const;

private:
    unordered_map<int, BusStop> busStops;
    vector<string> lines;

    static void sortLines(vector<string>& v) {
        sort(v.begin(), v.end(), [](const string& a, const string& b) {
            int numA = 0, numB = 0;
            size_t i = 0;
            while (i < a.size() && isdigit(a[i])) { numA = numA * 10 + (a[i] - '0'); ++i; }
            i = 0;
            while (i < b.size() && isdigit(b[i])) { numB = numB * 10 + (b[i] - '0'); ++i; }
            if (numA != numB) return numA < numB;
            return a < b; // ako su brojevi isti, leksikografski sort
        });
    }
};

#endif //FUNCTIONALITY_H
