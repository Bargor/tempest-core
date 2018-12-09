// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <core.h>
#include <platform.h>
#include <assert.h>


#include <chrono>
#include <cstdint>
#include <ratio>

namespace tst {
namespace core {

    class timer {
    private:
        using hr_clock = std::chrono::high_resolution_clock;
        using sys_clock = std::chrono::system_clock;

    public:
        template<typename U, typename T>
        using dur = std::chrono::duration<U, T>;

    public:
        timer() noexcept;
        ~timer() = default;

        void start() noexcept;
        void stop() noexcept;
        void reset() noexcept;
        std::chrono::microseconds get_time() const noexcept;
        bool started() const noexcept;

    private:
        hr_clock m_timer;
        std::chrono::time_point<hr_clock> m_lastStart;
        dur<std::int64_t, std::nano> m_elapsedTime;
        bool m_started;
    };

    TST_INLINE tst::core::timer::timer() noexcept : m_elapsedTime(std::chrono::nanoseconds::zero()), m_started(false) {}

    TST_INLINE void timer::start() noexcept {
        m_started = true;
        m_lastStart = m_timer.now();
    }

    TST_INLINE void timer::stop() noexcept {
        assert(m_started);
        m_elapsedTime += (m_timer.now() - m_lastStart);
        m_started = false;
    }

    TST_INLINE void timer::reset() noexcept {
        m_started = false;
        m_elapsedTime = std::chrono::nanoseconds::zero();
    }

    TST_INLINE std::chrono::microseconds timer::get_time() const noexcept {
        assert(!m_started);
        return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime);
    }

    TST_INLINE bool timer::started() const noexcept { return m_started; }

} // namespace util
} // namespace tst
