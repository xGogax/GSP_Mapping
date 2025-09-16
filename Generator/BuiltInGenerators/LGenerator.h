#ifndef LGENERATOR_H
#define LGENERATOR_H

#include "../Generator.h"
#include "../../Functionality.h"

class LGenerator : public Generator {
public:
    explicit LGenerator(const Functionality& f) : func(f) {}

    void build(const unordered_map<int, BusStop>& busStops) override;
    void print() const override;

private:
    const Functionality& func;
    unordered_map<int, unordered_set<int>> LGraph;
};

#endif