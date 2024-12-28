#include "MiningTruck.h"
#include <random>

int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

MiningTruck::MiningTruck(int id)
    : id(id), currentState(Mining), totalMiningTime(0),
      totalTravelingTime(0), totalUnloadingTime(0), miningDuration(0) {}

void MiningTruck::mine() {
    if (currentState == Mining) {
        miningDuration = getRandomNumber(1, 5) * 60;
        totalMiningTime += miningDuration;
        currentState = Traveling;
    }
}

void MiningTruck::travelToUnloadStation() {
    if (currentState == Traveling) {
        totalTravelingTime += 30;
        currentState = Unloading;
    }
}

void MiningTruck::unload() {
    if (currentState == Unloading) {
        totalUnloadingTime += 5;
        currentState = Mining;
    }
}

TruckState MiningTruck::getState() const {
    return currentState;
}

int MiningTruck::getMiningDuration() const{
    return miningDuration;
}

void MiningTruck::getStats() const {
    std::cout << "Truck " << id << " Stats:\n"
              << "  Total Mining Time: " << totalMiningTime << " minutes\n"
              << "  Total Traveling Time: " << totalTravelingTime << " minutes\n"
              << "  Total Unloading Time: " << totalUnloadingTime << " minutes\n";
}
