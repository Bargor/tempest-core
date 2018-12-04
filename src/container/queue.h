// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <array>
#include <atomic>
#include <core.h>
#include <optional>

namespace tst {
namespace core {

    // single producer single consumer lock free queue based on ring buffer

    template<typename T, std::size_t Size>
    class spsc_queue {
    public:
        using index_type = std::int32_t;

    public:
        spsc_queue() noexcept;

        bool try_push(const T& element) noexcept;
        std::optional<T> try_pop() noexcept;

    private:
        constexpr index_type next_pos(index_type idx) noexcept;

    private:
        static constexpr std::size_t bufferSize = Size + 1;
        std::array<T, bufferSize> m_buffer;
        std::atomic<int32_t> m_front;
        std::atomic<int32_t> m_back;
    };

    template<typename T, size_t Size>
    TST_INLINE spsc_queue<T, Size>::spsc_queue() noexcept : m_front(0), m_back(0) {
    }

    template<typename T, size_t Size>
    TST_INLINE bool spsc_queue<T, Size>::try_push(const T& element) noexcept {
        index_type frontPos = m_front.load(std::memory_order_relaxed);
        index_type newFront = next_pos(frontPos);

        if (newFront == m_back.load(std::memory_order_acquire)) // queue full can't push
            return false;

        m_buffer[frontPos] = element;
        m_front.store(newFront, std::memory_order_release);

        return true;
    }

    template<typename T, size_t Size>
    TST_INLINE std::optional<T> spsc_queue<T, Size>::try_pop() noexcept {
        index_type backPos = m_back.load(std::memory_order_relaxed);
        index_type frontPos = m_front.load(std::memory_order_acquire);

        if (frontPos == backPos) // queue empty, nother to read
            return std::nullopt;

        auto value = m_buffer[backPos];
        m_back.store(next_pos(backPos), std::memory_order_release);

        return value;
    }

    template<typename T, size_t Size>
    constexpr typename spsc_queue<T, Size>::index_type spsc_queue<T, Size>::next_pos(index_type idx) noexcept {
        return ++idx == bufferSize ? 0 : idx;
    }

} // namespace core
} // namespace tst
