#ifndef GENERATOR_H
#define GENERATOR_H

#include "../Skelet/BusStop.h"
#include <unordered_map>
#include <string>

using namespace std;

class Generator {
public:
    enum class Format { GML, CSV };

    explicit Generator(Format f = Format::GML) : format(f) {}

    virtual void build(const unordered_map<int, BusStop>& busStops) = 0;
    virtual void print() const = 0;
    virtual void exportGraph(const string& filename) const = 0;

    virtual ~Generator() = default;

protected:
    Format format;
};

#endif
