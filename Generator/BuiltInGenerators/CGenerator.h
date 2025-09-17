#ifndef CGENERATOR_H
#define CGENERATOR_H

#include "../Generator.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class CGenerator : public Generator {
public:
    explicit CGenerator(Format fmt = Format::GML) : Generator(fmt) {}

    void build(const unordered_map<int, BusStop>& busStops) override;
    void print() const override;
    void exportGraph(const string& filename) const override;

private:
    unordered_map<string, unordered_set<string>> CGraph;
};

#endif