cmake_minimum_required(VERSION 3.10)

# 1) Project definition
project(LunarMiningProject VERSION 1.0 LANGUAGES CXX)

# 2) Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3) Point CMake to your "include" folder for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# 4) Create a library from core source files
#    This library will be linked by both the main app and tests.
add_library(Lunar-Mining
    src/MiningTruck.cpp
    src/MiningStation.cpp
    src/Simulation.cpp
)

# 5) Create the main application (executable) from main.cpp
add_executable(lunar_mining_app
    src/main.cpp
)

# 6) Link the library to the main app
target_link_libraries(lunar_mining_app
    PRIVATE
    Lunar-Mining
)
