#include "Simulation.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>


using namespace MiningProcess;

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::numeric_limits;

Simulation::Simulation(int nTrucks, int nStations)
    : numTrucks_(nTrucks), numStations_(nStations), currentTime_(0)
    
    /* Constructs the simulation with the specified number of trucks and stations. */

{
    // Seed random num generator with current system time
    rng_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));

    // Create trucks
    trucks_.reserve(numTrucks_);
    for (int i = 0; i < numTrucks_; ++i) {
        trucks_.emplace_back(i); 
    }

    // Create stations
    stations_.reserve(numStations_);
    for (int i = 0; i < numStations_; ++i) {
        stations_.emplace_back(i);
    }
}

void Simulation::Run_() {
    /* Runs the entire simulation (72 hours or until the event queue is empty). */

    // Initialize trucks with random mining finish events
    for (int i = 0; i < numTrucks_; ++i) {
        int miningDuration = getRandomMiningDuration_();
        trucks_[i].AddMiningTime_(miningDuration);

        // Schedule the initial FINISH_MINING event
        scheduleEvent_(Process_{miningDuration, i, ProcessType_::FINISH_MINING});
    }

    // Process events until we exceed 72 hours or the queue is empty
    while (!eventQueue_.empty()) {
        Process_ evt = eventQueue_.top();
        eventQueue_.pop();

        // If this event time is beyond the simulation end time (72 hrs = 4320 min), ignore
        if (evt.Time_ > SIMULATION_DURATION_MINUTES_) {
            break;
        }

        // Advance current simulation time
        currentTime_ = evt.Time_;

        // Switch case to the appropriate event handler
        switch (evt.Type_) {
            case ProcessType_::FINISH_MINING:
                handleFinishMining_(evt);
                break;
            case ProcessType_::ARRIVE_STATION:
                handleArriveStation_(evt);
                break;
            case ProcessType_::FINISH_UNLOADING:
                handleFinishUnloading_(evt);
                break;
        }
    }

    reportStatistics_();
}

void Simulation::scheduleEvent_(const Process_ &evt) {
    /* Schedules a new event by pushing it into the priority queue. */

    eventQueue_.push(evt);
}

int Simulation::getRandomMiningDuration_() {
    /* Returns a random mining duration between 60 and 300 minutes. */

    std::uniform_int_distribution<int> dist(MIN_MINING_TIME_MIN_, MAX_MINING_TIME_MIN_);
    return dist(rng_);
}

void Simulation::handleFinishMining_(const Process_ &evt) {
    /* Handles the FINISH_MINING event for a truck. */

    int truckID = evt.TruckID_;

    // The truck travels to the station (30 min)
    trucks_[truckID].AddTravelTime_(TRAVEL_TIME_MIN_);

    // After traveling, schedule ARRIVE_STATION event
    int arrivalTime = currentTime_ + TRAVEL_TIME_MIN_;
    scheduleEvent_(Process_{arrivalTime, truckID, ProcessType_::ARRIVE_STATION});
}

void Simulation::handleArriveStation_(const Process_ &evt) {
    /* Handles the ARRIVE_STATION event for a truck. */

    int truckID = evt.TruckID_;

    // Find the earliest available station
    int earliestStation = -1;
    int earliestAvailability = numeric_limits<int>::max();

    for (int i = 0; i < numStations_; ++i) {
        int stationAvailable = stations_[i].GetBusyUntil_();
        if (stationAvailable < earliestAvailability) {
            earliestAvailability = stationAvailable;
            earliestStation = i;
        }
    }

    // The truck can only start unloading when the station is free
    int startUnloadingTime = std::max(earliestAvailability, currentTime_);
    int waitTime = startUnloadingTime - currentTime_;
    if (waitTime > 0) {
        trucks_[truckID].AddWaitingTime_(waitTime);
    }

    // Station busy from startUnloadingTime until finishUnloadingTime
    int finishUnloadingTime = startUnloadingTime + UNLOAD_TIME_MIN_;
    stations_[earliestStation].SetBusyUntil_(finishUnloadingTime);
    stations_[earliestStation].AddTimeBusy_(UNLOAD_TIME_MIN_);

    // Schedule the FINISH_UNLOADING event
    scheduleEvent_(Process_{
        finishUnloadingTime,
        truckID,
        ProcessType_::FINISH_UNLOADING
    });
}

void Simulation::handleFinishUnloading_(const Process_ &evt) {
    /* Handles the FINISH_UNLOADING event for a truck. */

    int truckID = evt.TruckID_;

    // Truck finished unloading
    trucks_[truckID].AddUnloadingTime_(UNLOAD_TIME_MIN_);
    trucks_[truckID].IncrementLoadsDelivered_();

    // Identify available station
    int usedStationID = findStationUsedForUnloading_(evt.Time_);
    if (usedStationID != -1) {
        stations_[usedStationID].IncrementLoadsHandled_();
    }

    // Travel back to mining site (30 min) then do random mining time again
    trucks_[truckID].AddTravelTime_(TRAVEL_TIME_MIN_);
    int nextMiningStart = currentTime_ + TRAVEL_TIME_MIN_;

    int miningDuration = getRandomMiningDuration_();
    trucks_[truckID].AddMiningTime_(miningDuration);

    int finishMiningTime = nextMiningStart + miningDuration;
    scheduleEvent_(Process_{finishMiningTime, truckID, ProcessType_::FINISH_MINING});
}

int Simulation::findStationUsedForUnloading_(int finishTime) {
    /* Finds which station just finished unloading at the given time. */

    for (size_t i = 0; i < stations_.size(); ++i) {
        if (stations_[i].GetBusyUntil_() == finishTime) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


void Simulation::reportStatistics_() {
    /* Prints final statistics for all trucks and stations. */

    cout << "\n=== Lunar Mining Simulation Report ===\n";
    cout << "Total simulation time: " << currentTime_ << " minutes / "
         << fixed << setprecision(2) << (currentTime_ / 60.0)
         << " hours (<= " << SIMULATION_DURATION_MINUTES_
         << " minutes, i.e. 72 hours)\n\n";

    cout << "---- Truck Statistics ----\n";
    for (int i = 0; i < numTrucks_; ++i) {
        const MiningTruck &t = trucks_[i];
        cout << "Truck " << (t.GetTruckID_() + 1)
             << ": Loads Delivered = " << t.GetLoadsDelivered_()
             << ", Mining Time = " << t.GetTotalMiningTime_()
             << ", Travel Time = " << t.GetTotalTravelTime_()
             << ", Waiting Time = " << t.GetTotalWaitingTime_()
             << ", Unloading Time = " << t.GetTotalUnloadingTime_()
             << ", Overall Time (hrs) = " << t.OverallTimeHours_()
             << endl;
    }

    cout << "\n---- Station Statistics ----\n";
    for (int i = 0; i < numStations_; ++i) {
        const Station &s = stations_[i];
        cout << "Station " << (s.GetStationID_() + 1)
             << ": Loads Handled = " << s.GetLoadsHandled_()
             << ", Total Busy Time = " << s.GetTotalBusyTime_()
             << ", Busy Until (final) = " << s.GetBusyUntil_()
             << endl;
    }
    cout << "\nSIMULATION COMPLETED\n";
}
