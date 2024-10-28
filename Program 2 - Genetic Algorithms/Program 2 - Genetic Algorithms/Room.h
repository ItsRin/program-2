// Jonin Villacampa

#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
public:
    std::string name;
    int capacity;

    Room(const std::string& name, int capacity) : name(name), capacity(capacity) {}
};

#endif
