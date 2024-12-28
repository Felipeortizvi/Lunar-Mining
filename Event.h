#ifndef EVENT_H
#define EVENT_H

#include <functional>

// Time is measured in minutes from the start of the simulation
enum class EventType {
    FINISH_MINING,
    ARRIVE_STATION,
    FINISH_UNLOADING
};

// Wwe store events in a priority_queue.
struct Event {
    int time;       // When the event occurs (minutes since start)
    int truckID;    // Which truck is affected
    EventType type; // FINISH_MINING, ARRIVE_STATION, FINISH_UNLOADING

    // For priority_queue sorting: earliest event first
    bool operator>(const Event &other) const {
        return time > other.time;
    }
};

#endif // EVENT_H