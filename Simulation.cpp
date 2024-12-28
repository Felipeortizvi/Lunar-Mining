#include "Simulation.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

Simulation::Simulation(int nTrucks, int nStations)
    : numTrucks(nTrucks), numStations(nStations), currentTime(0)
{
    // Seed the RNG with current time
    rng.seed(static_cast<unsigned long>(chrono::system_clock::now().time_since_epoch().count()));

    // Create trucks
    trucks.reserve(numTrucks);
    for (int i = 0; i < numTrucks; ++i) {
        trucks.emplace_back(i); // Insert value at the end of a vector
    }

    // Create stations
    stations.reserve(numStations);
    for (int i = 0; i < numStations; ++i) {
        stations.emplace_back(i); // Insert value at the end of a vector
    }
}

void Simulation::run() {
    // Initializing trucks with random mining finish events
    for (int i = 0; i < numTrucks; ++i) {
        int miningDuration = getRandomMiningDuration();
        trucks[i].addMiningTime(miningDuration);
        scheduleEvent(Event{ miningDuration, i, EventType::FINISH_MINING });
    }

    // Do events until time exceeds 72 hours
    while (!eventQueue.empty()) {
        Event evt = eventQueue.top();
        eventQueue.pop();

        // If this event time is beyond the simulation end time, stop
        if (evt.time > SIMULATION_DURATION_MINUTES) {
            break;
        }

        // Update clock to this event's time
        currentTime = evt.time;

        // Switch case event to correct handling logic
        switch (evt.type) {
            case EventType::FINISH_MINING:
                handleFinishMining(evt);
                break;
            case EventType::ARRIVE_STATION:
                handleArriveStation(evt);
                break;
            case EventType::FINISH_UNLOADING:
                handleFinishUnloading(evt);
                break;
        }
    }

    // Print final stats
    reportStatistics();
}

void Simulation::scheduleEvent(const Event &evt) {
    eventQueue.push(evt);
}

int Simulation::getRandomMiningDuration() {
    uniform_int_distribution<int> dist(MIN_MINING_TIME_MIN, MAX_MINING_TIME_MIN);
    return dist(rng);
}

// Mining State handlers (Whichever state the truck process is in, the logic is created here)
void Simulation::handleFinishMining(const Event &evt) {
    int truckID = evt.truckID;

    // Truck travels to station (30 min)
    trucks[truckID].addTravelTime(TRAVEL_TIME_MIN);

    int arrivalTime = currentTime + TRAVEL_TIME_MIN;
    scheduleEvent(Event{ arrivalTime, truckID, EventType::ARRIVE_STATION });
}

void Simulation::handleArriveStation(const Event &evt) {
    int truckID = evt.truckID;

    // Find earliest available station
    int earliestStation = -1;
    int earliestAvailability = numeric_limits<int>::max();

    for (int i = 0; i < numStations; ++i) {
        int stationAvailable = stations[i].getBusyUntil();
        if (stationAvailable < earliestAvailability) {
            earliestAvailability = stationAvailable;
            earliestStation = i;
        }
    }

    // The truck can only start unloading when the station is free
    int startUnloadingTime = max(earliestAvailability, currentTime);
    int waitTime = startUnloadingTime - currentTime;
    if (waitTime > 0) {
        trucks[truckID].addWaitingTime(waitTime);
    }

    int finishUnloadingTime = startUnloadingTime + UNLOAD_TIME_MIN;
    stations[earliestStation].setBusyUntil(finishUnloadingTime);
    stations[earliestStation].addTimeBusy(UNLOAD_TIME_MIN);

    // Schedule finish unloading
    scheduleEvent(Event{ finishUnloadingTime, truckID, EventType::FINISH_UNLOADING });
}

void Simulation::handleFinishUnloading(const Event &evt) {
    int truckID = evt.truckID;

    trucks[truckID].addUnloadingTime(UNLOAD_TIME_MIN);
    trucks[truckID].incrementLoadsDelivered();

    // Identify which station just finished unloading
    int usedStationID = findStationUsedForUnloading(evt.time);
    if (usedStationID != -1) {
        stations[usedStationID].incrementLoadsHandled();
    }

    // Now travel back to mining site, then random mining
    trucks[truckID].addTravelTime(TRAVEL_TIME_MIN);
    int nextMiningStart = currentTime + TRAVEL_TIME_MIN;

    int miningDuration = getRandomMiningDuration();
    trucks[truckID].addMiningTime(miningDuration);

    int finishMiningTime = nextMiningStart + miningDuration;
    scheduleEvent(Event{ finishMiningTime, truckID, EventType::FINISH_MINING });
}

int Simulation::findStationUsedForUnloading(int finishTime) {
    // Find the station whose busyUntil == finishTime
    for (size_t i = 0; i < stations.size(); ++i) {
        if (stations[i].getBusyUntil() == finishTime) {
            return static_cast<int>(i);
        }
    }
    return -1; 
}


// Simulation Statistics
void Simulation::reportStatistics() {
    cout << "\n=== Lunar Mining Status Update ===\n";
    cout << "Total simulation time: " << currentTime
              << " minutes (<= " << SIMULATION_DURATION_MINUTES << ")\n\n";

    cout << "---- Truck Statistics ----\n";
    for (int i = 0; i < numTrucks; ++i) {
        const MiningTruck &t = trucks[i];
        cout << "Truck " << t.getTruckID() + 1
                << ": Loads Delivered = " << t.getLoadsDelivered()
                << ", Mining Time = " << t.getTotalMiningTime()
                << ", Travel Time = " << t.getTotalTravelTime()
                << ", Waiting Time = " << t.getTotalWaitingTime()
                << ", Unloading Time = " << t.getTotalUnloadingTime()
                << "\n";
    }

    cout << "\n---- Station Statistics ----\n";
    for (int i = 0; i < numStations; ++i) {
        const Station &s = stations[i];
        cout << "Station " << s.getStationID() + 1
                << ": Loads Handled = " << s.getLoadsHandled()
                << ", Total Busy Time = " << s.getTotalBusyTime()
                << ", Busy Until (final) = " << s.getBusyUntil()
                << "\n";
    }
    cout << "==========================\n";
}
