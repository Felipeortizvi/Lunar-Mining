// Tests the Simulation Class

#include <gtest/gtest.h>
#include "Simulation.h"


class TestableSimulation : public Simulation {
public:
    using Simulation::Simulation;

    void setFixedSeed(unsigned long seed) {
        // Expose the internal rng for test reproducibility
        rng_.seed(seed);
    }
};

TEST(SimulationTest, BasicRun) {
    // Create a testable simulation with 2 trucks, 1 station
    TestableSimulation sim(2, 1);

    // Set the RNG to get exact results.
    sim.setFixedSeed(12345);

    sim.Run_();

    SUCCEED();
}

