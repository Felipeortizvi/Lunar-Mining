#include <iostream>
#include "Simulation.h"

int main(int argc, char** argv) {
    // You can modify the code here if you have the base argument
    int nTrucks = 4;
    int nStations = 3;

    // Allows the user to specify the number of trucks and stations as CLI arguments.
    // Sample run: 
    //      ./LunarSim.exe 4 10
    // This will run the simulation with 4 trucks and 10 stations.
    if (argc == 3) {
        nTrucks   = std::atoi(argv[1]);
        nStations = std::atoi(argv[2]);
    }

    std::cout << "Starting Lunar Helium-3 Mining Simulation\n";
    std::cout << "Number of Trucks: " << nTrucks << "\n";
    std::cout << "Number of Stations: " << nStations << "\n\n";

    // Build Sim Object and Run
    Simulation sim(nTrucks, nStations);
    sim.Run_();

    return 0;
}
