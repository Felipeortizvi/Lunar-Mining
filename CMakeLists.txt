cmake_minimum_required(VERSION 3.15)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL RESULT_VARIABLE _toolchainIncluded)
if(NOT _toolchainIncluded)
    message(WARNING 
        "Conan toolchain file not found! "
        "Please run 'conan install' before building.")
endif()

project(LunarMiningProject VERSION 1.0 LANGUAGES CXX)

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

# Make c++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(Lunar-Mining
    src/MiningTruck.cpp
    src/MiningStation.cpp
    src/Simulation.cpp
)
target_include_directories(Lunar-Mining
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Add executable
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

# Allows us to do testing for code
enable_testing()
find_package(GTest REQUIRED CONFIG)

message(STATUS "GTest include dirs: ${GTest_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTest_LIBRARIES}")

# Add executables
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

# Make googletests accessible
include(GoogleTest)
gtest_discover_tests(lunar_mining_tests)
