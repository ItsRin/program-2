// Jonin Villacampa

#include "Activity.h"
#include "Room.h"
#include "Facilitator.h"
#include "Schedule.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Activity> activities = {
        {"SLA100A", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}},
        {"SLA100B", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}},
        {"SLA191A", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}},
        {"SLA191B", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}},
        {"SLA201", 50, {"Glen", "Banks", "Zeldin", "Shaw"}, {"Numen", "Richards", "Singer"}},
        {"SLA291", 50, {"Lock", "Banks", "Zeldin", "Singer"}, {"Numen", "Richards", "Shaw", "Tyler"}},
        {"SLA303", 60, {"Glen", "Zeldin", "Banks"}, {"Numen", "Singer", "Shaw"}},
        {"SLA304", 25, {"Glen", "Banks", "Tyler"}, {"Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin"}},
        {"SLA394", 20, {"Tyler", "Singer"}, {"Richards", "Zeldin"}},
        {"SLA449", 60, {"Tyler", "Singer", "Shaw"}, {"Zeldin", "Uther"}},
        {"SLA451", 100, {"Tyler", "Singer", "Shaw"}, {"Zeldin", "Uther", "Richards", "Banks"}}
    };

    std::vector<Room> rooms = {
        {"Slater 003", 45},
        {"Roman 216", 30},
        {"Loft 206", 75},
        {"Roman 201", 50},
        {"Loft 310", 108},
        {"Beach 201", 60},
        {"Beach 301", 75},
        {"Logos 325", 450},
        {"Frank 119", 60}
    };

    std::vector<Facilitator> facilitators = {
        {"Lock"}, {"Glen"}, {"Banks"}, {"Richards"}, {"Shaw"},
        {"Singer"}, {"Uther"}, {"Tyler"}, {"Numen"}, {"Zeldin"}
    };

    GeneticAlgorithm ga(500, 100, activities, rooms, facilitators);
    Schedule bestSchedule = ga.run();

    std::cout << "Best Schedule Found:\n";
    bestSchedule.print();

    return 0;
}
