#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

using namespace std;

struct Location {
    Location(double lat, double lon) : lat(lat), lon(lon) {};

    double getLat() const { return lat; }
    double getLon() const { return lon; }
private:
    double lat;
    double lon;
};

#endif
