#ifndef WRONGDIRECTIONEXCEPTION_H
#define WRONGDIRECTIONEXCEPTION_H

#include <exception>
#include <string>

#include "../Exception.h"

class WrongDirectionException : public Exception {
public:
    WrongDirectionException () : Exception("ERROR: Direction is eather A or B!") {}
};

#endif
