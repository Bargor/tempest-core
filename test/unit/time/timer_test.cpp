// This file is part of Tempest-core project
// Author: Karol Kontny

#include "gtest/gtest.h"
#include <time/timer.h>
#include <fmt/printf.h>

using namespace tst::core;
using namespace std;

TEST(Timer, timerInit) {
    timer timer;
    EXPECT_EQ(timer.get_time(), chrono::duration<float>::zero());
}

TEST(Timer, timerStartStop) {
    timer timer;
    EXPECT_FALSE(timer.started());
    timer.start();
    EXPECT_TRUE(timer.started());
    timer.stop();
    EXPECT_FALSE(timer.started());
}

TEST(Timer, timerResolution) {
    timer timer;
    fmt::printf("%jd %jd %f\n",
           chrono::high_resolution_clock::period::num,
           chrono::high_resolution_clock::period::den,
           (double)chrono::high_resolution_clock::period::num / chrono::high_resolution_clock::period::den);
    EXPECT_EQ(timer.get_time(), chrono::duration<float>::zero());
}

TEST(Timer, timerStartStopDuration) {
    timer timer;
    timer.start();
    timer.stop();
    chrono::duration<double, std::micro> time = timer.get_time();
    printf("Timer start stop: %lf\n", time.count());
    EXPECT_TRUE(timer.get_time() < chrono::duration<float>(1.0f));
}

TEST(Timer, timerReset) {
    timer timer;
    EXPECT_FALSE(timer.started());
    timer.start();
    timer.stop();
    timer.reset();
    EXPECT_FALSE(timer.started());
    EXPECT_EQ(timer.get_time(), chrono::duration<float>::zero());
}
