#ifndef NOMEMORY_H
#define NOMEMORY_H

#include <string>

class nomemory {
private:
    int size;
public:
    nomemory(int s) : size(s) {}

    std::string message() const {
        return "Memory allocation failed for size: " + std::to_string(size);
    }
};

#endif // NOMEMORY_H
