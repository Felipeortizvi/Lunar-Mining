cmake_minimum_required(VERSION 3.15)

# If on a newer CMake, ensure we enable this policy (for MSVC runtime library configuration)
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

project(LunarMiningProject VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Core library: Lunar-Mining
# ------------------------------------------------------------------------------
add_library(Lunar-Mining
    src/MiningTruck.cpp
    src/MiningStation.cpp
    src/Simulation.cpp
)

# Make sure the library knows where to look for headers
target_include_directories(Lunar-Mining PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# ------------------------------------------------------------------------------
# Main application executable: lunar_mining_app
# ------------------------------------------------------------------------------
add_executable(lunar_mining_app
    src/main.cpp
)

target_include_directories(lunar_mining_app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(lunar_mining_app PRIVATE
    Lunar-Mining
)

# ------------------------------------------------------------------------------
# Testing setup with GoogleTest
# ------------------------------------------------------------------------------
enable_testing()

# After Conan has generated the find_package hooks, we can do:
find_package(GTest REQUIRED)

# Optional debug message to verify what GTest got picked up
message(STATUS "GTest include dirs: ${GTest_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTest_LIBRARIES}")

# Test executable
add_executable(lunar_mining_tests
    tests/test_MiningTruck.cpp
    tests/test_MiningStation.cpp
    tests/test_Simulation.cpp
)

# Include the project headers and GTest headers for the test build
target_include_directories(lunar_mining_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GTest_INCLUDE_DIRS}
)

# Link the test executable against the library and GTest
target_link_libraries(lunar_mining_tests PRIVATE
    Lunar-Mining
    GTest::gtest
    GTest::gtest_main
)

# Use automatic GoogleTest discovery
include(GoogleTest)
gtest_discover_tests(lunar_mining_tests)
