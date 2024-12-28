#ifndef MININGTRUCK_H
#define MININGTRUCK_H

#include <iostream>

enum TruckState { Mining, Traveling, Unloading };

class MiningTruck {
    int id;
    TruckState currentState;
    int totalMiningTime;
    int totalTravelingTime;
    int totalUnloadingTime;
    int miningDuration;

public:
    MiningTruck(int id);

    void mine();
    void travelToUnloadStation();
    void unload();
    TruckState getState() const;
    void getStats() const;
    int getMiningDuration() const;
};

#endif