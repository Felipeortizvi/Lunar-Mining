#include "MiningStation.h"

/// Minining station constructor
Station::Station(int id)
    : stationid_(id) {}

int Station::GetStationID_() const {
    return stationid_;
}

void Station::SetBusyUntil_(int time) {
    busyuntiltime_ = time;
}

int Station::GetBusyUntil_() const {
    return busyuntiltime_;
}

void Station::AddTimeBusy_(int duration) {
    totalBusyTime_ += duration;
}

void Station::IncrementLoadsHandled_() {
    loadsHandled_++;
}

int Station::GetTotalBusyTime_() const {
    return totalBusyTime_;
}

int Station::GetLoadsHandled_() const {
    return loadsHandled_;
}
