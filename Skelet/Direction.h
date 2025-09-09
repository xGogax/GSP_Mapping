#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include <vector>

#include "BusStop.h"

using namespace std;

class Direction {
public:
    Direction(const string &filename, const string &busNum) : filename(filename), busNum(busNum) {
        BusStop::fillMap(filename, busStopIDs);
    };

    vector<BusStop> getBusStops() {
        vector<BusStop> busStops;
        for (auto id : busStopIDs) {
            BusStop* bus_stop = BusStop::getBusStop(id);
            if (bus_stop == nullptr) continue;
            busStops.push_back(*bus_stop);
        }
        return busStops;
    }

    void addBussStop(string input) {
        size_t pos = input.find('!');
        if (pos != string::npos) {
            string brojStr = input.substr(0, pos);

            int id = stoi(brojStr);
            if (find(busStopIDs.begin(), busStopIDs.end(), id) != busStopIDs.end()) {
                cout << "Bus stop with ID " << id << " already exists!" << endl;
            } else {
                busStopIDs.push_back(id);
            }
        }
    }

    void removeBusStops() {
        for (int id : busStopIDs) {
            BusStop* bus_stop = BusStop::getBusStop(id);
            if (bus_stop == nullptr) continue;

            bus_stop->getBusLines().erase(busNum);
            if (bus_stop->getBusLines().empty()) {
                BusStop::removeFromMap(to_string(id));
            }
        }
    }

private:
    vector<int> busStopIDs;
    string filename;
    string busNum;
};

#endif
