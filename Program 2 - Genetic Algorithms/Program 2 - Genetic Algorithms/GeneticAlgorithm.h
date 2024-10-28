// Jonin Villacampa

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include "Schedule.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, int generations, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<Facilitator>& facilitators);
    Schedule run();

private:
    int populationSize;
    int generations;
    double mutationRate = 0.01;
    std::vector<Activity> activities;
    std::vector<Room> rooms;
    std::vector<Facilitator> facilitators;

    std::vector<Schedule> generateInitialPopulation();
    std::vector<Schedule> selection(const std::vector<Schedule>& population);
    Schedule crossover(const Schedule& parent1, const Schedule& parent2);
    void mutate(Schedule& schedule);
};

#endif
