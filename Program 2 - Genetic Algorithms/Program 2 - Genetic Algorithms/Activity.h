// Jonin Villacampa

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <vector>

class Activity {
public:
    std::string id;
    int expectedEnrollment;
    std::vector<std::string> preferredFacilitators;
    std::vector<std::string> otherFacilitators;

    Activity(const std::string& id, int enrollment, const std::vector<std::string>& preferred, const std::vector<std::string>& others)
        : id(id), expectedEnrollment(enrollment), preferredFacilitators(preferred), otherFacilitators(others) {}
};

#endif
