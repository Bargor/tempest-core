// This file is part of Tempest-core project
// Author: Karol Kontny

#include "gtest/gtest.h"
#include <util/bitpack.h>

using namespace tst::core;

TEST(bitpack, get_low) {
    std::uint64_t full = 0xAAAABBBBBBBBAAAA;
    std::uint32_t low = get_low_bits<std::uint64_t, std::uint32_t>(full);
    EXPECT_EQ(low, 0xBBBBAAAA);
}

TEST(bitpack, get_high) {
    std::uint64_t full = 0xAAAABBBBBBBBAAAA;
    std::uint32_t high = get_high_bits<std::uint64_t, std::uint32_t>(full);
    EXPECT_EQ(high, 0xAAAABBBB);
}

TEST(bitpack, combine) {
    std::uint32_t low = 0xBBBBAAAA;
    std::uint32_t high = 0xAAAABBBB;
    std::uint64_t full = combine<std::uint64_t, std::uint32_t>(high, low);
    EXPECT_EQ(full, 0xAAAABBBBBBBBAAAA);
}