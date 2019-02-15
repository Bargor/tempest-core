// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <core.h>
#include <platform.h>

#include <array>
#include <cstdint>
#include <random>

namespace tst {
namespace core {

    class complimentary_multiply_with_carry_engine {
    public:
        using result_type = std::uint32_t;

        constexpr complimentary_multiply_with_carry_engine(const std::uint32_t s = 0) noexcept;

        static constexpr result_type min() noexcept;
        static constexpr result_type max() noexcept;
        result_type operator()() noexcept;
        constexpr void seed(const std::uint32_t s) noexcept;

    private:
        static constexpr std::uint32_t m_PHI = 0x9e3779b9;
        static constexpr std::int64_t m_maxSeed = 18782;
        static constexpr std::uint32_t m_r = 0xfffffffe;
        static constexpr std::uint32_t m_size = 4096U;
        std::uint32_t m_it;
        std::uint32_t m_c;
        std::array<std::uint32_t, m_size> m_state;
    };

    using cmwc_engine = complimentary_multiply_with_carry_engine;

    constexpr cmwc_engine::complimentary_multiply_with_carry_engine(const std::uint32_t seed) noexcept
        : m_it(m_size - 1), m_c(362436), m_state({seed, seed + m_PHI, seed + m_PHI + m_PHI}) {
        for (std::uint32_t i = 3; i < m_size; i++)
            m_state[i] = m_state[i - 3] ^ m_state[i - 2] ^ m_PHI ^ i;
    }

    constexpr cmwc_engine::result_type cmwc_engine::min() noexcept {
        return 0;
    }

    constexpr cmwc_engine::result_type cmwc_engine::max() noexcept {
        return 0xFFFFFFFF;
    }

    TST_INLINE cmwc_engine::result_type cmwc_engine::operator()() noexcept {
        std::uint64_t t;
        std::uint32_t x;
        m_it = (m_it + 1) & (m_size - 1);
        t = m_maxSeed * m_state[m_it] + m_c;
        m_c = (t >> 32);
        x = static_cast<std::uint32_t>(t + m_c);
        if (x < m_c) {
            x++;
            m_c++;
        }
        return (m_state[m_it] = m_r - x);
    }

    constexpr void cmwc_engine::seed(const std::uint32_t seed) noexcept {
        m_state[0] = seed;
        m_state[1] = seed + m_PHI;
        m_state[2] = seed + m_PHI + m_PHI;
        for (std::uint32_t i = 3; i < m_size; i++)
            m_state[i] = m_state[i - 3] ^ m_state[i - 2] ^ m_PHI ^ i;
    }

} // namespace core
} // namespace tst
