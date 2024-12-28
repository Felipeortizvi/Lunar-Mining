#include "MiningTruck.h"

MiningTruck::MiningTruck(int id) : truckID(id){}

int MiningTruck::getTruckID() const {
    return truckID;
}

void MiningTruck::addMiningTime(int minutes) {
    totalMiningTime += minutes;
}

void MiningTruck::addTravelTime(int minutes) {
    totalTravelTime += minutes;
}

void MiningTruck::addWaitingTime(int minutes) {
    totalWaitingTime += minutes;
}

void MiningTruck::addUnloadingTime(int minutes) {
    totalUnloadingTime += minutes;
}

void MiningTruck::incrementLoadsDelivered() {
    loadsDelivered++;
}

int MiningTruck::getTotalMiningTime() const {
    return totalMiningTime;
}

int MiningTruck::getTotalTravelTime() const {
    return totalTravelTime;
}

int MiningTruck::getTotalWaitingTime() const {
    return totalWaitingTime;
}

int MiningTruck::getTotalUnloadingTime() const {
    return totalUnloadingTime;
}

int MiningTruck::getLoadsDelivered() const {
    return loadsDelivered;
}