#ifndef STATION_H
#define STATION_H

class Station {
public:
    explicit Station(int id);

    int getStationID() const;

    // Busy until this time means the station is occupied until busyUntilTime
    void setBusyUntil(int time);
    int getBusyUntil() const;

    // Station-level statistics
    void addTimeBusy(int duration);
    void incrementLoadsHandled();

    int getTotalBusyTime() const;
    int getLoadsHandled() const;

private:
    int stationID;
    int busyUntilTime = 0; // minute mark until which station is busy

    // Stats
    int totalBusyTime = 0;
    int loadsHandled  = 0;
};

#endif
