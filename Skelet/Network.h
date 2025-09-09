#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

#include "Line.h"

using namespace std;

class Network {
public:
    Network() {
        lines = vector<Line>();
    };

    void addLine(string input) {
        Line l = Line::createLine(input);
        this->lines.push_back(l);
    }

    void addBusStop(string busNum, string dir, string input);
    void removeBusStop(string busStopID);
    void removeLine(string busNum);

    void printBusStops(string busNum) const;

private:
    vector<Line> lines;
};

#endif
