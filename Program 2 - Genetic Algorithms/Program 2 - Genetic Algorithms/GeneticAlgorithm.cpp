// Jonin Villacampa

#include "GeneticAlgorithm.h"
#include <algorithm>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(int popSize, int gens, const std::vector<Activity>& acts, const std::vector<Room>& rms, const std::vector<Facilitator>& facs)
    : populationSize(popSize), generations(gens), activities(acts), rooms(rms), facilitators(facs) {}

std::vector<Schedule> GeneticAlgorithm::generateInitialPopulation() {
    std::vector<Schedule> population;
    for (int i = 0; i < populationSize; ++i) {
        Schedule schedule;
        for (const auto& activity : activities) {
            Schedule::Assignment assignment = {
                activity,
                Schedule::getRandomRoom(rooms),
                Schedule::getRandomFacilitator(facilitators),
                Schedule::getRandomTimeSlot()
            };
            schedule.assignments.push_back(assignment);
        }
        population.push_back(schedule);
    }
    return population;
}

std::vector<Schedule> GeneticAlgorithm::selection(const std::vector<Schedule>& population) {
    std::vector<Schedule> selected = population;
    std::sort(selected.begin(), selected.end(), [](const Schedule& a, const Schedule& b) {
        return a.calculateFitness() > b.calculateFitness();
        });
    selected.resize(populationSize / 2);
    return selected;
}

Schedule GeneticAlgorithm::crossover(const Schedule& parent1, const Schedule& parent2) {
    Schedule child;
    for (size_t i = 0; i < parent1.assignments.size(); ++i) {
        child.assignments.push_back(i % 2 == 0 ? parent1.assignments[i] : parent2.assignments[i]);
    }
    return child;
}

void GeneticAlgorithm::mutate(Schedule& schedule) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    if (dis(gen) < mutationRate) {
        int i = static_cast<int>(gen() % schedule.assignments.size());
        schedule.assignments[i].room = Schedule::getRandomRoom(rooms);
        schedule.assignments[i].facilitator = Schedule::getRandomFacilitator(facilitators);
        schedule.assignments[i].timeSlot = Schedule::getRandomTimeSlot();
    }
}

Schedule GeneticAlgorithm::run() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto population = generateInitialPopulation();
    for (int generation = 0; generation < generations; ++generation) {
        population = selection(population);
        while (population.size() < static_cast<size_t>(populationSize)) {
            Schedule parent1 = population[gen() % (populationSize / 2)];
            Schedule parent2 = population[gen() % (populationSize / 2)];
            Schedule child = crossover(parent1, parent2);
            mutate(child);
            population.push_back(child);
        }
    }
    return *std::max_element(population.begin(), population.end(), [](const Schedule& a, const Schedule& b) {
        return a.calculateFitness() < b.calculateFitness();
        });
}
