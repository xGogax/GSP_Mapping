#ifndef CGENERATOR_H
#define CGENERATOR_H

#include "../Generator.h"

class CGenerator : public Generator {
public:
    void build(const unordered_map<int, BusStop>& busStops) override;
    void print() const override;
private:
    unordered_map<string, unordered_set<string>> CGraph;
};

#endif
