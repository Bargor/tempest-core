// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <thread>

namespace tst {
namespace core {

    struct main_thread {
    public:
        static std::thread::id get_id() noexcept;

    private:
        const static std::thread::id m_id;
    };

    inline std::thread::id main_thread::get_id() noexcept { return m_id; }

} // namespace core
} // namespace tst