#ifndef MININGSTATION_H
#define MININGSTATION_H

/// A class representing a single mining station that can service unloading operations.
class Station {
public:
    /// Constructs a Station with a given ID.
    explicit Station(int id);

    /// Returns this station's ID.
    int GetStationID_() const;

    /// Sets the minute mark until which this station is busy.
    void SetBusyUntil_(int time);

    /// Returns the minute mark until which this station is busy.
    int GetBusyUntil_() const;

    /// Adds the specified duration to this station's total busy time.
    void AddTimeBusy_(int duration);

    /// Increments the number of loads handled by this station.
    void IncrementLoadsHandled_();

    /// Returns this station's total busy time in minutes.
    int GetTotalBusyTime_() const;

    /// Returns the total loads handled by this station.
    int GetLoadsHandled_() const;

private:
    int stationid_;         ///< Unique ID for this station.
    int busyuntiltime_{0};  ///< Minute mark until which the station is busy.

    int totalBusyTime_{0};  ///< Accumulated busy time of this station (minutes).
    int loadsHandled_{0};   ///< Number of loads handled by this station.
};

#endif 
