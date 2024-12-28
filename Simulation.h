#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include <random>
#include <limits>
#include "MiningProcess.h"
#include "MiningTruck.h"
#include "MiningStation.h"

// The Simulation class orchestrates the entire 72-hour mining operation.
class Simulation {
public:
    Simulation(int nTrucks, int nStations);

    // Run the entire simulation (72 hours or until event queue empty)
    void run();

private:
    // Simulation duration in minutes: 72 hours = 4320 minutes
    static const int SIMULATION_DURATION_MINUTES = 72 * 60;

    // Constants for mining times, travel times, unload times
    static const int MIN_MINING_TIME_MIN = 60;   // 1 hour
    static const int MAX_MINING_TIME_MIN = 300;  // 5 hours
    static const int TRAVEL_TIME_MIN     = 30;
    static const int UNLOAD_TIME_MIN     = 5;

    // Number of trucks and stations
    int numTrucks;
    int numStations;

    // Current simulation time (minutes)
    int currentTime;

    // Containers for trucks and stations
    std::vector<MiningTruck> trucks;
    std::vector<Station> stations;

    // Priority queue of events (min-heap by event time)
    std::priority_queue<Process, std::vector<Process>, std::greater<Process>> eventQueue;

    // Random number generator
    std::mt19937 rng;

private:
    // Helper functions
    void scheduleEvent(const Process &evt);
    int getRandomMiningDuration();

    // Event handlers
    void handleFinishMining(const Process &evt);
    void handleArriveStation(const Process &evt);
    void handleFinishUnloading(const Process &evt);

    // Helper method to find which station just finished unloading
    int findStationUsedForUnloading(int finishTime);

    // Final reporting
    void reportStatistics();
};

#endif
