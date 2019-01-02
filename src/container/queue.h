// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <array>
#include <atomic>
#include <core.h>
#include <optional>
#include <util/bitpack.h>

namespace tst {
namespace core {

    // single producer single consumer lock free queue based on ring buffer

    template<typename T, std::size_t Size>
    class spsc_queue {
    public:
        using index_type = std::int32_t;

    public:
        spsc_queue() noexcept;

        bool empty() noexcept;

        bool try_push(const T& element) noexcept;
        // This one has overwrite semantics when queue is full, will overwrite oldest item
        void push(const T& element) noexcept;
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
    TST_INLINE bool spsc_queue<T, Size>::empty() noexcept {
        index_type frontPos = m_front.load(std::memory_order_relaxed);
        index_type backPos = m_back.load(std::memory_order_relaxed);

        return backPos == frontPos;
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
    TST_INLINE void spsc_queue<T, Size>::push(const T& element) noexcept {
        index_type frontPos = m_front.load(std::memory_order_acquire);
        index_type newFront = next_pos(frontPos);

        m_buffer[frontPos] = element;
        m_front.store(newFront, std::memory_order_release);
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

    // single producer multiple consumer lock free queue based on ring buffer
    template<typename T, std::size_t Size>
    class spmc_queue {
    public:
        using index_type = std::uint32_t;
        using store_type = std::uint64_t;

    public:
        spmc_queue() noexcept;

        bool empty() noexcept;

        bool try_push(const T& element) noexcept;
        // This one has overwrite semantics when queue is full, will overwrite oldest item
        void push(const T& element) noexcept;
        std::optional<T> try_pop() noexcept;

    private:
        constexpr index_type next_pos(index_type idx) noexcept;

    private:
        union index_descriptor {

            std::atomic<store_type> full;
            std::array<std::atomic<index_type>, 2> half;

            index_descriptor(store_type num) : full(num) {}
            index_descriptor(index_type back, index_type front) : half{{back, front}} {}
            
        };


    private:
        static constexpr std::size_t bufferSize = Size + 1;
        std::array<T, bufferSize> m_buffer;
        index_descriptor m_positions;

        static_assert(sizeof(index_descriptor) == sizeof(uint64_t));
    };

    template<typename T, size_t Size>
    TST_INLINE spmc_queue<T, Size>::spmc_queue() noexcept : m_positions(0) {
    }

    template<typename T, size_t Size>
    TST_INLINE bool spmc_queue<T, Size>::empty() noexcept {
        store_type positions = m_positions.full.load(std::memory_order_acquire);
        index_type front = get_high_bits<store_type, index_type>(positions);
        index_type back = get_low_bits<store_type, index_type>(positions);

        return front == back;
    }

    template<typename T, size_t Size>
    TST_INLINE bool spmc_queue<T, Size>::try_push(const T& element) noexcept {
        store_type positions = m_positions.full.load(std::memory_order_acquire);
        index_type front = get_high_bits<store_type, index_type>(positions);
        index_type back = get_low_bits<store_type, index_type>(positions);

        index_type next_front = next_pos(front);

        if (next_front == back) {
            return false;
        }

        m_buffer[front] = element;
        m_positions.half[1].store(next_front, std::memory_order_release);
        return true;
    }

    template<typename T, size_t Size>
    TST_INLINE std::optional<T> spmc_queue<T, Size>::try_pop() noexcept {
        while (true) {
            store_type positions = m_positions.full.load(std::memory_order_acquire);
            index_type front = get_high_bits<store_type, index_type>(positions);
            index_type back = get_low_bits<store_type, index_type>(positions);

            if (front == back) {
                return std::nullopt;
            }

            auto value = m_buffer[back];

            if (m_positions.half[0].compare_exchange_strong(back, next_pos(back), std::memory_order_acq_rel)) {
                return value;
            }
        } 
    }

    template<typename T, size_t Size>
    constexpr typename spmc_queue<T, Size>::index_type spmc_queue<T, Size>::next_pos(index_type idx) noexcept {
        return ++idx == bufferSize ? 0 : idx;
    }

} // namespace core
} // namespace tst
