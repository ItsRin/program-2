// Jonin Villacampa

#include "Schedule.h"
#include <cmath>
#include <unordered_map>

double Schedule::calculateFitness() const {
    double fitness = 0.0;
    const int hours[] = { 10, 11, 12, 1, 2, 3 };

    std::unordered_map<std::string, int> facilitatorActivityCount;
    std::unordered_map<int, std::unordered_map<std::string, bool>> roomSchedule;

    for (const auto& assignment : assignments) {
        if (roomSchedule[assignment.timeSlot][assignment.room.name]) {
            fitness -= 0.5; 
        }
        else {
            roomSchedule[assignment.timeSlot][assignment.room.name] = true;
        }

        if (assignment.room.capacity < assignment.activity.expectedEnrollment) {
            fitness -= 0.5;
        }
        else if (assignment.room.capacity > 3 * assignment.activity.expectedEnrollment) {
            fitness -= (assignment.room.capacity > 6 * assignment.activity.expectedEnrollment) ? 0.4 : 0.2;
        }
        else {
            fitness += 0.3;
        }

        if (std::find(assignment.activity.preferredFacilitators.begin(), assignment.activity.preferredFacilitators.end(), assignment.facilitator.name) != assignment.activity.preferredFacilitators.end()) {
            fitness += 0.5;
        }
        else if (std::find(assignment.activity.otherFacilitators.begin(), assignment.activity.otherFacilitators.end(), assignment.facilitator.name) != assignment.activity.otherFacilitators.end()) {
            fitness += 0.2;
        }
        else {
            fitness -= 0.1;
        }

        facilitatorActivityCount[assignment.facilitator.name]++;
    }

    for (const auto& count : facilitatorActivityCount) {
        const std::string& facilitator = count.first;
        int numActivities = count.second;

        if (numActivities == 1) {
            fitness += 0.2; 
        }
        else if (numActivities > 1) {
            fitness -= 0.2; 
        }
        if (numActivities > 4) {
            fitness -= 0.5; 
        }
        if (numActivities == 1 || numActivities == 2) {
            if (facilitator != "Tyler") {
                fitness -= 0.4; 
            }
        }
    }

    int sla101TimeSlots[2] = { -1, -1 }; 
    int sla191TimeSlots[2] = { -1, -1 }; 

    for (size_t i = 0; i < assignments.size(); ++i) {
        const auto& assignment = assignments[i];
        if (assignment.activity.id == "SLA101A") sla101TimeSlots[0] = assignment.timeSlot;
        if (assignment.activity.id == "SLA101B") sla101TimeSlots[1] = assignment.timeSlot;
        if (assignment.activity.id == "SLA191A") sla191TimeSlots[0] = assignment.timeSlot;
        if (assignment.activity.id == "SLA191B") sla191TimeSlots[1] = assignment.timeSlot;
    }

    if (sla101TimeSlots[0] != -1 && sla101TimeSlots[1] != -1) {
        int gap = std::abs(sla101TimeSlots[1] - sla101TimeSlots[0]);
        if (gap > 4) fitness += 0.5;
        if (gap == 0) fitness -= 0.5;
    }

    if (sla191TimeSlots[0] != -1 && sla191TimeSlots[1] != -1) {
        int gap = std::abs(sla191TimeSlots[1] - sla191TimeSlots[0]);
        if (gap > 4) fitness += 0.5;
        if (gap == 0) fitness -= 0.5;
    }

    for (int t1 : sla101TimeSlots) {
        for (int t2 : sla191TimeSlots) {
            if (t1 != -1 && t2 != -1) {
                int gap = std::abs(t1 - t2);
                if (gap == 1) fitness += 0.5;
                if (gap == 2) fitness += 0.25;
                if (gap == 0) fitness -= 0.25;

                if (gap == 1) {
                    bool oneInRomanOrBeach = assignments[t1].room.name.find("Roman") != std::string::npos ||
                        assignments[t1].room.name.find("Beach") != std::string::npos;
                    bool otherInRomanOrBeach = assignments[t2].room.name.find("Roman") != std::string::npos ||
                        assignments[t2].room.name.find("Beach") != std::string::npos;
                    if (oneInRomanOrBeach != otherInRomanOrBeach) fitness -= 0.4;
                }
            }
        }
    }

    return fitness;
}
