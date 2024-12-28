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

# # 7) Enable testing features in CMake
# enable_testing()

# # 8) Find Google Test (if installed system-wide or via vcpkg)
# #    If GTest is not found, you will need to manually provide its path or add_subdirectory.
# find_package(GTest CONFIG REQUIRED) 
# # If not using CONFIG mode, you might do: find_package(GTest REQUIRED)

# # 9) Create a test executable that contains all your test files
# add_executable(lunar_mining_tests
#     tests/test_truck.cpp
#     tests/test_station.cpp
#     tests/test_simulation.cpp
# )

# # 10) Link the same library plus GTest libs
# target_link_libraries(lunar_mining_tests
#     PRIVATE
#     lunar_mining
#     GTest::gtest
#     GTest::gtest_main
# )

# # 11) Register the test executable with CTest so you can run "ctest"
# add_test(NAME AllTests COMMAND lunar_mining_tests)
