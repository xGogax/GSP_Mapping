#include "ZoneFilter.h"

unordered_set<string> ZoneFilter::apply(const unordered_map<int, BusStop> &busStops,
    const vector<string> &allLines) const {
    unordered_set<string> remainingLines;

    for (const auto& line : allLines) {
        unordered_set<int> lineZones;

        // Skupi sve zone kroz koje prolazi data linija
        for (const auto& pair : busStops) {
            const BusStop& stop = pair.second;
            const auto& busLines = stop.getBusLines();
            if (busLines.find(line) != busLines.end()) {
                lineZones.insert(stop.getZone());
            }
        }

        if (lineZones == zones) {
            remainingLines.insert(line);
        }
    }

    return remainingLines;
}
