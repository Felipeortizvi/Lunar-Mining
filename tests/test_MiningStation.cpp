// Tests the MiningStation Class

#include <gtest/gtest.h>
#include "MiningStation.h"

TEST(StationTest, DefaultConstructor) {
    Station s(0);

    EXPECT_EQ(s.GetStationID_(), 0);
    EXPECT_EQ(s.GetBusyUntil_(), 0);
    EXPECT_EQ(s.GetTotalBusyTime_(), 0);
    EXPECT_EQ(s.GetLoadsHandled_(), 0);
}

TEST(StationTest, BusyUntilLogic) {
    Station s(1);

    s.SetBusyUntil_(100);
    EXPECT_EQ(s.GetBusyUntil_(), 100);

    // Set new busy time
    s.SetBusyUntil_(200);
    EXPECT_EQ(s.GetBusyUntil_(), 200);
}

TEST(StationTest, StationStats) {
    Station s(2);

    // Add busy time
    s.AddTimeBusy_(5);
    EXPECT_EQ(s.GetTotalBusyTime_(), 5);

    s.AddTimeBusy_(10);
    EXPECT_EQ(s.GetTotalBusyTime_(), 15);


    s.IncrementLoadsHandled_();
    s.IncrementLoadsHandled_();
    EXPECT_EQ(s.GetLoadsHandled_(), 2);
}
