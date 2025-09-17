#ifndef STATIONNOTEXISTS_H
#define STATIONNOTEXISTS_H

#include <exception>
#include <string>

#include "../Exception.h"

class StationNotExists : public Exception{
public:
    StationNotExists(const std::string& stationID) : Exception("Station " + stationID + " does not exists"){}
};


#endif //STATIONNOTEXISTS_H
