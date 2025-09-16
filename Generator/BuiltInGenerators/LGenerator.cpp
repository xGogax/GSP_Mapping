#include "LGenerator.h"

void LGenerator::build(const unordered_map<int, BusStop>& busStops) {
    LGraph.clear();

    for (const auto& [stopID, stop] : busStops) {
        auto nextStops = func.getNextStops(stopID, false);

        for (const auto& ns : nextStops) {
            int nextID = ns.first;
            LGraph[stopID].insert(nextID);
            LGraph[nextID].insert(stopID);
        }
    }
}

void LGenerator::print() const {
    for (const auto& [stop, neighbors] : LGraph) {
        cout << "Stajaliste " << stop << " je povezano sa: ";
        for (int n : neighbors) {
            cout << n << " ";
        }
        cout << endl;
    }
}
