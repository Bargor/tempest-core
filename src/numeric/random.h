// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <array>
#include <core>
#include <cstdint>
#include <platform>
#include <random>

namespace tst {
namespace core {

    class multiply_with_carry_engine {
    public:
        constexpr multiply_with_carry_engine(const std::uint32_t s = 0) noexcept;
        using result_type = std::uint32_t;

        static constexpr result_type min() noexcept;
        static constexpr result_type max() noexcept;
        result_type operator()() noexcept;
        constexpr void seed(const std::uint32_t s) noexcept;

    private:
        static constexpr std::uint32_t m_PHI = 0x9e3779b9;
        static constexpr std::int64_t m_maxSeed = 18782;
        static constexpr std::uint32_t m_r = 0xffffffe;
        static constexpr std::uint32_t m_size = 4096U;
        std::array<std::uint32_t, m_size> m_state;
        std::uint32_t m_seed;
        std::uint32_t m_it;
    };

    constexpr multiply_with_carry_engine::multiply_with_carry_engine(const std::uint32_t s) noexcept
        : m_seed(s), m_it(m_size - 1), m_state({m_seed, m_seed + m_PHI, m_seed + m_PHI + m_PHI}) {
        for (std::int32_t i = 3; i < m_size; i++)
            m_state[i] = m_state[i - 3] ^ m_state[i - 2] ^ m_PHI ^ i;
    }

    constexpr multiply_with_carry_engine::result_type multiply_with_carry_engine::min() noexcept {
        return 0;
    }

    constexpr multiply_with_carry_engine::result_type multiply_with_carry_engine::max() noexcept {
        return 0xFFFFFFFF;
    }

    TST_INLINE multiply_with_carry_engine::result_type multiply_with_carry_engine::operator()() noexcept {
        std::uint64_t t;
        std::uint32_t x;
        m_it = (m_it + 1) & (m_size - 1);
        t = m_maxSeed * m_state[m_it] + m_seed;
        m_seed = (t >> 32);
        x = static_cast<std::uint32_t>(t + m_seed);
        if (x < m_seed) {
            x++;
            m_seed++;
        }
        return (m_state[m_it] = m_r - x);
    }

    constexpr void multiply_with_carry_engine::seed(const std::uint32_t s) noexcept {
        m_seed = s;
        m_state[0] = m_seed;
        m_state[1] = m_seed + m_PHI;
        m_state[2] = m_seed + m_PHI + m_PHI;
        for (std::int32_t i = 3; i < m_size; i++)
            m_state[i] = m_state[i - 3] ^ m_state[i - 2] ^ m_PHI ^ i;
    }

} // namespace core
} // namespace tst
