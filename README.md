## Lunar Mining Simulator

Task is to develop a simulation for a lunar Helium-3 space mining operation. This
simulation will manage and track the efficiency of mining trucks and unload stations over a
continuous 72-hour operation.

## Key Components

Mining Trucks: These vehicles perform the actual mining tasks.

Mining Sites: Locations on the moon where the trucks extract Helium-3. Assume an infinite
number of sites, ensuring trucks always have access to mine without waiting.

Mining Unload Stations: Designated stations where trucks unload the mined Helium-3. Each
station can handle one truck at a time.


## Simulation Requirements:

The simulation must be configurable to accommodate various numbers of mining trucks (n)
and unload stations (m).

Calculate and report statistics for the performance and efficiency of each mining truck and
unload station.

The simulation represents 72 hours of non-stop mining and must execute faster than
real-time to provide timely analysis.

## Run Executable Program

`cd build`

`./LunarSim.exe`

or

`./LunarSim.exe 4 3`  eg. Arguement for n = 4 Trucks, and m = 3 Stations.

## Compiling The Code

`cd ../Lunar-Mining/build/`

`cmake ..`

`cmake --build`

`./Debug/lunar_mining_app.exe`

## Updated Compilation Steps

`cd build`

`conan install .. --build=missing -s build_type=Debug`

`cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug`

`cmake --build .`

## Run Tests

For a simple run through of tests:
`ctest` 

For a more detailed analysis of tests:
`ctest --verbose`


## Run Code

`cd ../build/debug`

`./lunar_mining_app.exe`
