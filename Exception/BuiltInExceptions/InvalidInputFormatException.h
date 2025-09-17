#ifndef INVALIDINPUTFORMATEXCEPTION_H
#define INVALIDINPUTFORMATEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class InvalidInputFormatException : public Exception{
public:
    InvalidInputFormatException(const std::string& line) : Exception("ERROR: {" + line + "} Invalid Format"){};
};

#endif
