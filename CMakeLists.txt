cmake_minimum_required(VERSION 3.10)

# 1) Project definition
project(LunarMiningProject VERSION 1.0 LANGUAGES CXX)

# 2) Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3) Set consistent runtime library
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

# 4) Include project headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# 5) Create a library from core source files
add_library(Lunar-Mining
    src/MiningTruck.cpp
    src/MiningStation.cpp
    src/Simulation.cpp
)

# 6) Create the main application (executable)
add_executable(lunar_mining_app
    src/main.cpp
)

# 7) Link the library to the main app
target_link_libraries(lunar_mining_app PRIVATE Lunar-Mining)

# 8) Add GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)

# 9) Enable testing
enable_testing()

# 10) Add the test executable
add_executable(lunar_mining_tests tests/test_MiningTruck.cpp)

# 11) Link the library and GTest to the test executable
target_link_libraries(lunar_mining_tests
    PRIVATE
    Lunar-Mining
    GTest::gtest
    GTest::gtest_main
)

# 12) Discover GoogleTest tests
include(GoogleTest)
gtest_discover_tests(lunar_mining_tests)
