#ifndef OUTOFBOUND_H
#define OUTOFBOUND_H

#include <string>

class outofbound {
public:
    std::string message() const {
        return "Out of bound access!";
    }
};

#endif // OUTOFBOUND_H
