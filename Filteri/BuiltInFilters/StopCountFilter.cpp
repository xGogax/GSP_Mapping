#include "StopCountFilter.h"

unordered_set<string> StopCountFilter::apply(const unordered_map<int, BusStop> &busStops,
    const vector<string> &lines) const {
    unordered_set<string> filteredLines;

    for (const auto& line : lines) {
        int count = 0;

        // prebroji koliko stanica prolazi kroz ovu liniju
        for (const auto& [id, stop] : busStops) {
            const BusStop& bs = stop;
            const auto& busLines = bs.getBusLines();
            if (busLines.find(line) != busLines.end()) {
                count++;
            }
        }

        // filtriraj na osnovu opcije
        if ((option == 1 && count < x) || (option == 2 && count > x)) {
            filteredLines.insert(line);
        }
    }

    return filteredLines;
}
