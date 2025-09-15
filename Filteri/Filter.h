#ifndef FILTER_H
#define FILTER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "../Skelet/BusStop.h"
#include "BuiltInFilters/ZoneFilter.h"
#include "BuiltInFilters/NumberFilter.h"
#include "BuiltInFilters/StopCountFilter.h"

using namespace std;

class Filter {
public:
    Filter() : busStops(BusStop::getBusStops()) {
        for (auto& pair : busStops) {
            const BusStop& stop = pair.second;
            for (const auto& line : stop.getBusLines()) {
                if (std::find(lines.begin(), lines.end(), line) == lines.end()) {
                    lines.push_back(line);
                }
            }
        }
    };

    void apply(int number) {
        auto printLines = [](const unordered_set<string>& lines) {
            cout << "Filtered lines: ";
            for (const auto& line : lines) cout << line << " ";
            cout << endl;
        };

        if (number == 1) { // FILTER ZONA
            cout << "Koje zone zelite (1 = {1}, 2 = {1,2}, 3 = {1,2,3}): ";
            int x; cin >> x;

            vector<int> zones;
            if (x == 1) zones = {1};
            else if (x == 2) zones = {1,2};
            else if (x == 3) zones = {1,2,3};

            ZoneFilter zf(zones);
            auto filteredLines = zf.apply(busStops, lines);
            printLines(filteredLines);

        } else if (number == 2) { // FILTER PO BROJU LINIJE
            cout << "Izaberite opciju:\n1. Broj linije manji od X\n2. Broj linije veci od X\n3. Broj linije izmedju X i Y\n";
            int option; cin >> option;

            int x, y = 0;
            if (option == 1 || option == 2) {
                cout << "Unesite broj X: "; cin >> x;
            } else {
                cout << "Unesite broj X i Y: "; cin >> x >> y;
            }

            NumberFilter nf(option, x, y);
            auto filteredLines = nf.apply(lines);
            printLines(filteredLines);

        } else if (number == 3) { // FILTER PO BROJU STAJALISTA
            cout << "Izaberite opciju:\n1. Manje od X\n2. Vece od X\n";
            int option; cin >> option;

            int x;
            cout << "Unesite broj X: "; cin >> x;

            StopCountFilter scf(option, x);
            auto filteredLines = scf.apply(busStops, lines);
            printLines(filteredLines);
        }
    }


    void printLines() const {
        cout << "Lines: ";
        for (const auto& line : lines) {
            cout << line << " ";
        }
        cout << endl;
    }

protected:
    unordered_map<int, BusStop> busStops;
    vector<string> lines;
};

#endif