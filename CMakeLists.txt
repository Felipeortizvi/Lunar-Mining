cmake_minimum_required(VERSION 3.15)

# -----------------------------------------------------
# Add these lines to use the Conan toolchain
# -----------------------------------------------------
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL RESULT_VARIABLE _toolchainIncluded)
if(NOT _toolchainIncluded)
    message(WARNING 
        "Conan toolchain file not found! "
        "Please run 'conan install' before building.")
endif()

project(LunarMiningProject VERSION 1.0 LANGUAGES CXX)

# If on a newer CMake, we enable this policy (for MSVC runtime library configuration)
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------
# Add your library
# --------------------------------
add_library(Lunar-Mining
    src/MiningTruck.cpp
    src/MiningStation.cpp
    src/Simulation.cpp
)
target_include_directories(Lunar-Mining
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# --------------------------------
# Add your main application
# --------------------------------
add_executable(lunar_mining_app
    src/main.cpp
)
target_include_directories(lunar_mining_app
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(lunar_mining_app PRIVATE
    Lunar-Mining
)

# --------------------------------
# Add GTest (from Conan) + your tests
# --------------------------------
enable_testing()
find_package(GTest REQUIRED CONFIG)  
# Note: If Conan’s GTest package only provides a standard module, use: find_package(GTest REQUIRED)

message(STATUS "GTest include dirs: ${GTest_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTest_LIBRARIES}")

add_executable(lunar_mining_tests
    tests/test_MiningTruck.cpp
    tests/test_MiningStation.cpp
    tests/test_Simulation.cpp
)
target_include_directories(lunar_mining_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GTest_INCLUDE_DIRS}
)
target_link_libraries(lunar_mining_tests PRIVATE
    Lunar-Mining
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lunar_mining_tests)
