// Jonin Villacampa

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include "Activity.h"
#include "Room.h"
#include "Facilitator.h"

class Schedule {
public:
    struct Assignment {
        Activity activity;
        Room room;
        Facilitator facilitator;
        int timeSlot;
    };

    std::vector<Assignment> assignments;

    double calculateFitness() const;

    static int getRandomTimeSlot() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 5);
        return dis(gen);
    }

    static Room getRandomRoom(const std::vector<Room>& rooms) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, rooms.size() - 1);
        return rooms[dis(gen)];
    }

    static Facilitator getRandomFacilitator(const std::vector<Facilitator>& facilitators) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(facilitators.size() - 1));
        return facilitators[dis(gen)];
    }

    void print() const {
        const std::vector<std::string> timeSlots = { "10 AM", "11 AM", "12 PM", "1 PM", "2 PM", "3 PM" };

        for (const auto& assignment : assignments) {
            std::cout << "Activity: " << assignment.activity.id
                << ", Room: " << assignment.room.name
                << ", Facilitator: " << assignment.facilitator.name
                << ", Time: " << timeSlots[assignment.timeSlot] << "\n";
        }
    }
};

#endif