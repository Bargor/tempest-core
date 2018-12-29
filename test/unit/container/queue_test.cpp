// This file is part of Tempest-core project
// Author: Karol Kontny

#include "gtest/gtest.h"
#include <container/queue.h>
#include <future>
#include <thread>

using namespace tst::core;

TEST(spsc_queue, test_push_than_pop) {
    constexpr std::int32_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spsc_queue, test_empty) {
    constexpr std::int32_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    EXPECT_TRUE(queue.empty());
}

TEST(spsc_queue, test_not_empty) {
    constexpr std::int32_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    EXPECT_TRUE(queue.empty());

    queue.try_push(1);

    EXPECT_FALSE(queue.empty());
}

TEST(spsc_queue, test_push_fail) {
    constexpr std::int32_t size = 31;

    spsc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    EXPECT_FALSE(queue.try_push(32));

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spsc_queue, test_pop_fail) {
    constexpr std::int32_t size = 32;

    spsc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }

    EXPECT_FALSE(queue.try_pop());
}

TEST(spsc_queue, test_push_pop_interleaved) {
    constexpr std::int32_t size = 1023;

    spsc_queue<std::int32_t, size> queue;

    std::promise<void> enabler;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        for (std::int32_t i = 0; i < size; ++i) {
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
    constexpr std::int32_t size = 1023;

    spsc_queue<std::int32_t, size> queue;

    std::promise<void> enabler;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        std::int32_t count = 0;

        while (count < 2 * size) {
            auto res = queue.try_push(count);
            if (res) ++count;
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

TEST(spmc_queue, test_empty) {
    constexpr std::int32_t size = 31;

    spmc_queue<std::int32_t, size> queue;

    EXPECT_TRUE(queue.empty());
}

TEST(spmc_queue, test_not_empty) {
    constexpr std::int32_t size = 31;

    spmc_queue<std::int32_t, size> queue;

    EXPECT_TRUE(queue.empty());

    queue.try_push(1);

    EXPECT_FALSE(queue.empty());
}

TEST(spmc_queue, test_push_than_pop) {
    constexpr std::int32_t size = 31;

    spmc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spmc_queue, test_push_fail) {
    constexpr std::int32_t size = 31;

    spmc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    EXPECT_FALSE(queue.try_push(32));

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }
}

TEST(spmc_queue, test_pop_fail) {
    constexpr std::int32_t size = 32;

    spmc_queue<std::int32_t, size> queue;

    for (std::int32_t i = 0; i < size; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    for (std::int32_t i = 0; i < size; ++i) {
        auto res = queue.try_pop();
        EXPECT_EQ(i, res.value());
    }

    EXPECT_FALSE(queue.try_pop());
}

TEST(spmc_queue, test_push_pop_interleaved) {
    constexpr std::int32_t size = 1023;
    std::vector<std::int32_t> items(size, 0);

    spmc_queue<std::int32_t, size> queue;

    std::atomic<std::int32_t> count = 0;

    std::promise<void> enabler;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        for (std::int32_t i = 0; i < size; ++i) {
            EXPECT_TRUE(queue.try_push(i));
            items[i] = 1;
        }
    };

    auto pop_queue = [&]() {
        notifier.wait();

        auto last = 0;
        while (count < size) {
            auto res = queue.try_pop();
            if (res) {
                EXPECT_LE(last, res.value());
                last = res.value();
                count++;
                items[last] = 2;
            }
        }
    };

    std::thread producer(push_queue);
    std::thread consumer_1(pop_queue);
    std::thread consumer_2(pop_queue);

    enabler.set_value();

    producer.join();
    consumer_1.join();
    consumer_2.join();

    for (auto i : items) {
        EXPECT_EQ(i, 2);
    }
}

TEST(spmc_queue, test_push_pop_interleaved_2) {
    constexpr std::int32_t size = 1023;
    constexpr std::int32_t mult = 2;
    std::vector<std::int32_t> items(size * mult, 0);

    spmc_queue<std::int32_t, size> queue;

    std::promise<void> enabler;

    std::atomic<std::int32_t> pop_count = 0;

    auto notifier = enabler.get_future().share();

    auto push_queue = [&]() {
        notifier.wait();

        std::int32_t count = 0;

        while (count < mult * size) {
            auto res = queue.try_push(count);
            if (res) {
                items[count] = 1;
                ++count;
            }
        }
    };

    auto pop_queue = [&]() {
        notifier.wait();

        auto last = 0;

        while (pop_count < 2 * size) {
            auto res = queue.try_pop();
            if (res) {
                EXPECT_LE(last, res.value());
                last = res.value();
                pop_count++;
                items[last] = 2;
            }
        }
    };

    std::thread producer(push_queue);
    std::thread consumer_1(pop_queue);
    std::thread consumer_2(pop_queue);

    enabler.set_value();

    producer.join();
    consumer_1.join();
    consumer_2.join();

    for (auto i : items) {
        EXPECT_EQ(i, 2);
    }
}