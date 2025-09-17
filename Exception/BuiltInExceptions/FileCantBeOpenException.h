#ifndef FILECANTBEOPEN_H
#define FILECANTBEOPEN_H

#include <exception>
#include <string>

#include "../Exception.h"

class FileCantBeOpenException : public Exception {
public:
    FileCantBeOpenException() : Exception("ERROR: File Can't be open") {}
};

#endif //FILECANTBEOPEN_H
