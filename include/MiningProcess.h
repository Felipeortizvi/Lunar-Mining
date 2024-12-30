#ifndef MININGPROCESS_H
#define MININGPROCESS_H

namespace MiningProcess {

    enum class ProcessType_ {
        FINISH_MINING,
        ARRIVE_STATION,
        FINISH_UNLOADING
    };

    struct Process_ {
        int Time_;              // When this process occurs (minutes since start)
        int TruckID_;           // Which truck is affected
        ProcessType_ Type_; 

        // Comparator for priority_queue (earliest event first)
        bool operator>(const Process_ &other) const {
            return Time_ > other.Time_;
        }
    };
}

#endif
