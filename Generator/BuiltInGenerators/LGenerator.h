#ifndef LGENERATOR_H
#define LGENERATOR_H

#include "../Generator.h"
#include "../../Functionality.h"
#include <fstream>

class LGenerator : public Generator {
public:
    explicit LGenerator(const Functionality& f, Format fmt = Format::GML)
        : Generator(fmt), func(f) {}

    void build(const unordered_map<int, BusStop>& busStops) override;
    void print() const override;
    void exportGraph(const string& filename) const override;

private:
    const Functionality& func;
    unordered_map<int, unordered_set<int>> LGraph;
};

#endif