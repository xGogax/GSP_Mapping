#ifndef GENERATOR_H
#define GENERATOR_H

#include "../Skelet/BusStop.h"
#include <unordered_map>

using namespace std;

class Generator {
public:
    virtual void build(const unordered_map<int, BusStop>& busStops) = 0;
    virtual void print() const = 0;
    virtual ~Generator() = default;
};

#endif
