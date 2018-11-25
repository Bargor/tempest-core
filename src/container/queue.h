// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <atomic>
#include <array>
#include <core>

namespace tst {
namespace core {

    // single producer single consumer lock free queue based on ring buffer

    template<typename T, size_t Size>
    class spsc_queue { 

    public:

        bool push(const T& element);
        bool pop(T& element);

    private:

        core::array<T, Size> m_buffer;
        core::atomic<uint32_t> m_front;
        core::atomic<uint32_t> m_back;
    };

}
}
