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
    // Constructs the simulation with the specified number of trucks and stations.
    Simulation(int nTrucks, int nStations);

    // Runs the entire simulation (72 hours or until the event queue is empty).
    void Run_();

protected:

    // Random number generator for mining durations.
    std::mt19937 rng_;

private:
    // The total simulation duration in minutes: 72 hours = 4320 minutes.
    static const int SIMULATION_DURATION_MINUTES_ = 72 * 60;

    // Constants for mining times, travel times, and unload times.
    static const int MIN_MINING_TIME_MIN_ = 60;   // Minimum: 1 hour (60 minutes)
    static const int MAX_MINING_TIME_MIN_ = 300;  // Maximum: 5 hours (300 minutes)
    static const int TRAVEL_TIME_MIN_     = 30;   // Travel time: 30 minutes
    static const int UNLOAD_TIME_MIN_     = 5;    // Unload time: 5 minutes

    // The number of trucks in this simulation.
    int numTrucks_;

    // The number of stations in this simulation.
    int numStations_;

    // The current simulation time (in minutes).
    int currentTime_;

    // A container of mining trucks.
    std::vector<MiningTruck> trucks_;

    // A container of mining stations.
    std::vector<Station> stations_;

    // Priority queue of events (min-heap by event time).
    std::priority_queue<
        MiningProcess::Process_, 
        std::vector<MiningProcess::Process_>, 
        std::greater<MiningProcess::Process_>> eventQueue_;

private:
    // Schedules a new event by pushing it into the priority queue.
    void scheduleEvent_(const MiningProcess::Process_ &evt);

    // Returns a random mining duration between MIN_MINING_TIME_MIN_ and MAX_MINING_TIME_MIN_.
    int getRandomMiningDuration_();

    // Handles the FINISH_MINING event for a truck.
    void handleFinishMining_(const MiningProcess::Process_ &evt);

    // Handles the ARRIVE_STATION event for a truck.
    void handleArriveStation_(const MiningProcess::Process_ &evt);

    // Handles the FINISH_UNLOADING event for a truck.
    void handleFinishUnloading_(const MiningProcess::Process_ &evt);

    // Finds which station just finished unloading at the given time.
    int findStationUsedForUnloading_(int finishTime);

    // Prints final statistics for all trucks and stations.
    void reportStatistics_();
};

#endif
