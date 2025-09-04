#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include <vector>

#include "BusStop.h"

using namespace std;

class Direction {
public:
    Direction(const string &filename) : filename(filename) {
        BusStop::fillMap(filename, busStops);
        printDirection();
    };

    void printDirection() const;
private:

    vector<BusStop> busStops;
    string filename;
};

#endif
