//
// Created by gogac on 9/16/2025.
//

#include "CGenerator.h"

void CGenerator::build(const unordered_map<int, BusStop> &busStops) {
    CGraph.clear();

    // Prolazimo kroz sva stajalista
    for (const auto& [stopID, stop] : busStops) {
        const auto& lines = stop.getBusLines();
        for (auto it1 = lines.begin(); it1 != lines.end(); ++it1) {
            for (auto it2 = next(it1); it2 != lines.end(); ++it2) {
                // povezi linije sa zajednickim stajalistem
                CGraph[*it1].insert(*it2);
                CGraph[*it2].insert(*it1);
            }
        }
    }
}

void CGenerator::print() const {
    cout << "C-Model (Lines as nodes):\n";
    for (const auto& [line, neighbors] : CGraph) {
        cout << "Line " << line << " -> ";
        for (const auto& n : neighbors) {
            cout << n << " ";
        }
        cout << "\n";
    }
}