#include <iostream>
#include "Simulation.h"

int main(int argc, char** argv) {
    // Default simulation settings
    int nTrucks = 3;
    int nStations = 2;

    // Optionally parse from command line
    if (argc == 3) {
        // nTrucks   = std::stoi(argv[1]);
        // nStations = std::stoi(argv[2]);

        nTrucks   = std::atoi(argv[1]);
        nStations = std::atoi(argv[2]);
    }

    std::cout << "Starting Lunar Helium-3 Mining Simulation\n";
    std::cout << "Number of Trucks: " << nTrucks << "\n";
    std::cout << "Number of Stations: " << nStations << "\n\n";

    // Build Sim Object and Run
    Simulation sim(nTrucks, nStations);
    sim.run();

    return 0;
}
