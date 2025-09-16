#ifndef FILTER_H
#define FILTER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
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
        sortLines(lines);
    };

    void apply(int number) {
        auto printLines = [this]() {
            const vector<string>& target = filteredLines.empty() ? lines : filteredLines;
            cout << "Filtered lines: ";
            for (const auto& line : target) cout << line << " ";
            cout << endl;
        };

        vector<string>& targetLines = filteredLines.empty() ? filteredLines : filteredLines;
        const vector<string>& currentLines = filteredLines.empty() ? lines : filteredLines;

        switch (number) {
            case 1: { // FILTER ZONA
                cout << "Koje zone zelite (1 = {1}, 2 = {1,2}, 3 = {1,2,3}): ";
                int x; cin >> x;

                vector<int> zones;
                if (x == 1) zones = {1};
                else if (x == 2) zones = {1,2};
                else if (x == 3) zones = {1,2,3};

                ZoneFilter zf(zones);
                auto result = zf.apply(busStops, currentLines);
                assignFiltered(result);
                printLines();
                break;
            }

            case 2: { // FILTER PO BROJU LINIJE
                cout << "Izaberite opciju:\n1. Broj linije manji od X\n2. Broj linije veci od X\n3. Broj linije izmedju X i Y\n";
                int option; cin >> option;

                int x, y = 0;
                if (option == 1 || option == 2) {
                    cout << "Unesite broj X: "; cin >> x;
                } else {
                    cout << "Unesite broj X i Y: "; cin >> x >> y;
                }

                NumberFilter nf(option, x, y);
                auto result = nf.apply(currentLines);
                assignFiltered(result);
                printLines();
                break;
            }

            case 3: { // FILTER PO BROJU STAJALISTA
                cout << "Izaberite opciju:\n1. Manje od X\n2. Vece od X\n";
                int option; cin >> option;

                int x;
                cout << "Unesite broj X: "; cin >> x;

                StopCountFilter scf(option, x);
                auto result = scf.apply(busStops, currentLines);
                assignFiltered(result);
                printLines();
                break;
            }

            case 4: { // RESET FILTERA
                filteredLines.clear();
                cout << "Filteri su otkazani, sve linije su ponovo dostupne.\n";
                break;
            }

            default:
                cout << "Nepoznata opcija filtera.\n";
                break;
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
    vector<string> filteredLines;

private:
    // sortiranje linija numericki + sufiks (npr. 25 < 25P)
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

    void assignFiltered(const unordered_set<string>& result) {
        filteredLines.assign(result.begin(), result.end());
        sortLines(filteredLines);
    }
};

#endif