// This file is part of Tempest-core project
// Author: Karol Kontny

#include "gtest/gtest.h"
#include <container/queue.h>
#include <future>
#include <thread>

using namespace tst::core;

TEST(spsc_queue, test_push_than_pop) {
    constexpr std::size_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    for (int i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (int i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spsc_queue, test_push_fail) {
    constexpr std::size_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    for (int i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    EXPECT_FALSE(queue.try_push(32));

    for (int i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spsc_queue, test_pop_fail) {
    constexpr std::size_t size = 32;

    spsc_queue<std::int32_t, size> queue;

    for (int i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (int i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }

    EXPECT_FALSE(queue.try_pop());
}

TEST(spsc_queue, test_push_pop_interleaved) {
    constexpr std::size_t size = 1023;

    spsc_queue<std::int32_t, size> queue;

    std::promise<void> enabler;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        for (int i = 0; i < size; ++i) {
            EXPECT_TRUE(queue.try_push(i));
        }
    };

    auto pop_queue = [&]() {
        notifier.wait();

        std::int32_t count = 0;

        while (count < size) {
            auto res = queue.try_pop();
            if (res) {
                EXPECT_EQ(count++, res.value());
            }
        }
    };

    std::thread producer(push_queue);
    std::thread consumer(pop_queue);

    enabler.set_value();

    producer.join();
    consumer.join();
}

TEST(spsc_queue, test_push_pop_interleaved_2) {
    constexpr std::size_t size = 1023;

    spsc_queue<std::int32_t, size> queue;

    std::promise<void> enabler;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        for (int i = 0; i < 2 * size; ++i) {
            EXPECT_TRUE(queue.try_push(i));
        }
    };

    auto pop_queue = [&]() {
        notifier.wait();

        std::int32_t count = 0;

        while (count < 2 * size) {
            auto res = queue.try_pop();
            if (res) {
                EXPECT_EQ(count++, res.value());
            }
        }
    };

    std::thread producer(push_queue);
    std::thread consumer(pop_queue);

    enabler.set_value();

    producer.join();
    consumer.join();
}