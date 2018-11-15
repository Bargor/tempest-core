// This file is part of Tempest-core project
// Author: Karol Kontny

#include "gtest/gtest.h"
#include <numeric/random.h>

using namespace tst::core;

TEST(random, randomGenerationInt)
{
    multiply_with_carry_engine random_generator;
    std::uniform_int_distribution<std::uint32_t> dist;
    std::uint32_t random = dist(random_generator);
    EXPECT_EQ(random, 268435454U);
}

TEST(random, setSeed)
{
    multiply_with_carry_engine random_generator;
    random_generator.seed(10000);
    std::uniform_int_distribution<std::uint32_t> dist;
    std::uint32_t random = dist(random_generator);
    EXPECT_EQ(random, 80605454U);
}

TEST(random, randomGenerationFloat)
{
    multiply_with_carry_engine random_generator;
    std::uniform_real_distribution<float> dist;
    float random = dist(random_generator);
    EXPECT_GT(random, 0.0f);
    EXPECT_LT(random, 1.0f);
}
