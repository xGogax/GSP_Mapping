#ifndef STOPCOUNTFILTER_H
#define STOPCOUNTFILTER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "../../Skelet/BusStop.h"

using namespace std;

class StopCountFilter {
public:
    // option: 1 = manji od, 2 = veci od
    StopCountFilter(int option, int x) : option(option), x(x) {}

    unordered_set<string> apply(const unordered_map<int, BusStop>& busStops, const vector<string>& lines) const;

private:
    int option;
    int x;
};

#endif