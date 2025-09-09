#ifndef BUSSTOP_H
#define BUSSTOP_H

#include <string>
#include <regex>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include "Location.h"

using namespace std;

class BusStop {
public:
    static void fillMap(string filename, vector<int>& vecID);
    static void removeFromMap(const string &busStopID) {
        BusStops.erase(stoi(busStopID));
    }

    static void printMap();

    int getIdBusStop() const{
        return idBusStop;
    }
    string getName() const {
        return name;
    }
    Location getLocation() const {
        return location;
    }
    unsigned int getZone() const {
        return zone;
    }

    unordered_set<string> &getBusLines(){
        return busLines;
    }

    static BusStop* getBusStop(int key) {
        if(BusStops.find(key) == BusStops.end()) {
            return nullptr;
        }
        return &BusStops.find(key)->second;
    }

    static void addBusStop(string input, string busNum) {
        createBusStop(input, busNum);
    }

private:
    BusStop(int idBusStop, const string &name, double lat, double lon, unsigned int zone)
    : idBusStop(idBusStop), name(name), location(lat, lon), zone(zone) {
        //moramo ucitati prazan vektor
        busLines = unordered_set<string>();
    };

    static BusStop createBusStop(string input, string busNum);

    int idBusStop;
    string name;
    Location location;
    unsigned int zone; //int > 0

    unordered_set<string> busLines;

    static unordered_map<int, BusStop> BusStops;
};

#endif
