#include "MiningTruck.h"
#include <cmath>

 /* Mining Truck constructor */
MiningTruck::MiningTruck(int id) : truckid_(id) {}

int MiningTruck::GetTruckID_() const {
    return truckid_;
}

void MiningTruck::AddMiningTime_(int minutes) {
    totalMiningTime_ += minutes;
}

void MiningTruck::AddTravelTime_(int minutes) {
    totalTravelTime_ += minutes;
}

void MiningTruck::AddWaitingTime_(int minutes) {
    totalWaitingTime_ += minutes;
}

void MiningTruck::AddUnloadingTime_(int minutes) {
    totalUnloadingTime_ += minutes;
}

void MiningTruck::IncrementLoadsDelivered_() {
    loadsDelivered_++;
}

int MiningTruck::GetTotalMiningTime_() const {
    return totalMiningTime_;
}

int MiningTruck::GetTotalTravelTime_() const {
    return totalTravelTime_;
}

int MiningTruck::GetTotalWaitingTime_() const {
    return totalWaitingTime_;
}

int MiningTruck::GetTotalUnloadingTime_() const {
    return totalUnloadingTime_;
}

int MiningTruck::GetLoadsDelivered_() const {
    return loadsDelivered_;
}

double MiningTruck::OverallTimeHours_() const {
    /* Sum all time (in minutes) and then convert to hours */
    
    double totalMinutes = static_cast<double>(
        totalMiningTime_ + totalTravelTime_ + totalWaitingTime_ + totalUnloadingTime_
    );
    double totalHours = totalMinutes / 60.0;

    // Round to two decimal places
    return std::round(totalHours * 100.0) / 100.0;
}
