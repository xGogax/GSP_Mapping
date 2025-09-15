#ifndef ZONEFILTER_H
#define ZONEFILTER_H

#include "../../Skelet/BusStop.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ZoneFilter {
public:
    ZoneFilter(const vector<int>& allowedZones) : zones(allowedZones.begin(), allowedZones.end()) {}

    unordered_set<string> apply(const unordered_map<int, BusStop>& busStops, const vector<string>& allLines) const;

private:
    unordered_set<int> zones;
};

#endif