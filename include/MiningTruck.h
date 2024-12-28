#ifndef MININGTRUCK_H
#define MININGTRUCK_H

class MiningTruck {
public:
    explicit MiningTruck(int id);

    int getTruckID() const;

    // Statistics accumulation
    void addMiningTime(int minutes);
    void addTravelTime(int minutes);
    void addWaitingTime(int minutes);
    void addUnloadingTime(int minutes);
    void incrementLoadsDelivered();

    // Getters for final report
    int getTotalMiningTime() const;
    int getTotalTravelTime() const;
    int getTotalWaitingTime() const;
    int getTotalUnloadingTime() const;
    int getLoadsDelivered() const;
    
    double overallTimeHours() const;

private:
    int truckID;

    // truck statistic values
    int totalMiningTime   = 0;
    int totalTravelTime   = 0;
    int totalWaitingTime  = 0;
    int totalUnloadingTime= 0;
    int loadsDelivered    = 0;
};

#endif
