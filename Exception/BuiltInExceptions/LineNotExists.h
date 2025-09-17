#ifndef LINENOTEXISTS_H
#define LINENOTEXISTS_H

#include <exception>
#include <string>

#include "../Exception.h"

class LineNotExists : public Exception {
public:
    LineNotExists (const std::string& busNum) : Exception("ERROR: Line " + busNum + " not exists.") {}
};

#endif //LINENOTEXISTS_H
