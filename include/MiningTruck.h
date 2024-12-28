#ifndef MININGTRUCK_H
#define MININGTRUCK_H

/// A class representing a single mining truck in the lunar mining simulation.
class MiningTruck {

public:
    /// Constructs a MiningTruck with a given ID.
    explicit MiningTruck(int id);

    /// Returns this truck's ID.
    int GetTruckID_() const;

    /// Adds to this truck's accumulated mining time (in min).
    void AddMiningTime_(int minutes);

    /// Adds to this truck's accumulated travel time (in min).
    void AddTravelTime_(int minutes);

    /// Adds to this truck's accumulated waiting time (in min).
    void AddWaitingTime_(int minutes);

    /// Adds to this truck's accumulated unloading time (in min).
    void AddUnloadingTime_(int minutes);

    /// Increments the count of loads delivered by this truck.
    void IncrementLoadsDelivered_();

    /// Returns the total mining time this truck has spent (in min).
    int GetTotalMiningTime_() const;

    /// Returns the total travel time this truck has spent (in min).
    int GetTotalTravelTime_() const;

    /// Returns the total waiting time this truck has spent (in min).
    int GetTotalWaitingTime_() const;

    /// Returns the total unloading time this truck has spent (in min).
    int GetTotalUnloadingTime_() const;

    /// Returns how many loads this truck has delivered.
    int GetLoadsDelivered_() const;

    /// Returns this truck's overall operating time (in hours), rounded to two decimals.
    double OverallTimeHours_() const;

private:
    int truckid_;                /// The unique ID for this truck

    int totalMiningTime_{0};     /// Accumulated mining time in minutes
    int totalTravelTime_{0};     /// Accumulated travel time in minutes
    int totalWaitingTime_{0};    /// Accumulated waiting time in minutes
    int totalUnloadingTime_{0};  /// Accumulated unloading time in minutes
    int loadsDelivered_{0};      /// Number of loads delivered
};

#endif
