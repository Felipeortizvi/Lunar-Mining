
#include <gtest/gtest.h>
#include "MiningTruck.h"

// Basic construction and default values
TEST(TruckTest, DefaultConstructor) {
    MiningTruck t(0);  // truck ID = 0 for this test

    EXPECT_EQ(t.GetTruckID_(), 0);
    EXPECT_EQ(t.GetTotalMiningTime_(), 0);
    EXPECT_EQ(t.GetTotalTravelTime_(), 0);
    EXPECT_EQ(t.GetTotalWaitingTime_(), 0);
    EXPECT_EQ(t.GetTotalUnloadingTime_(), 0);
    EXPECT_EQ(t.GetLoadsDelivered_(), 0);
}

// Check if adding mining time accumulates properly
TEST(TruckTest, MiningTimeAccumulation) {
    MiningTruck t(1);

    t.AddMiningTime_(50);
    EXPECT_EQ(t.GetTotalMiningTime_(), 50);

    t.AddMiningTime_(30);
    EXPECT_EQ(t.GetTotalMiningTime_(), 80);
}

// Check travel, waiting, unloading times similarly
TEST(TruckTest, AddOtherTimes) {
    MiningTruck t(2);

    t.AddTravelTime_(30);
    EXPECT_EQ(t.GetTotalTravelTime_(), 30);

    t.AddWaitingTime_(10);
    EXPECT_EQ(t.GetTotalWaitingTime_(), 10);

    t.AddUnloadingTime_(5);
    EXPECT_EQ(t.GetTotalUnloadingTime_(), 5);
}

// Check loads delivered
TEST(TruckTest, LoadsDelivered) {
    MiningTruck t(3);
    t.IncrementLoadsDelivered_();
    EXPECT_EQ(t.GetLoadsDelivered_(), 1);

    t.IncrementLoadsDelivered_();
    EXPECT_EQ(t.GetLoadsDelivered_(), 2);
}