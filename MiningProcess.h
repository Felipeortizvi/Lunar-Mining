#ifndef MININGPROCESS_H
#define MININGPROCESS_H

#include <functional>

// Time is measured in minutes from the start of the simulation
enum class ProcessType {
    FINISH_MINING,
    ARRIVE_STATION,
    FINISH_UNLOADING
};

// We store Processes in a priority_queue.
struct Process {
    int time;       // When the event occurs (minutes since start)
    int truckID;    // Which truck is affected
    ProcessType type; // FINISH_MINING, ARRIVE_STATION, FINISH_UNLOADING

    // For priority_queue sorting: earliest event first
    bool operator>(const Process &other) const {
        return time > other.time;
    }
};

#endif
