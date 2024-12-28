#include "MiningStation.h"

Station::Station(int id) : stationID(id){}

int Station::getStationID() const {
    return stationID;
}

void Station::setBusyUntil(int time) {
    busyUntilTime = time;
}

int Station::getBusyUntil() const {
    return busyUntilTime;
}

void Station::addTimeBusy(int duration) {
    totalBusyTime += duration;
}

void Station::incrementLoadsHandled() {
    loadsHandled++;
}

int Station::getTotalBusyTime() const {
    return totalBusyTime;
}

int Station::getLoadsHandled() const {
    return loadsHandled;
}
