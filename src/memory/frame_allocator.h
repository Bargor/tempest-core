// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <core.h>
#include <memory_resource>
#include <atomic>
#include <vector>

namespace tst {
namespace core {

    class frame_allocator : public std::pmr::memory_resource {
    public:
        using pointer = void*;

        frame_allocator(std::size_t size);
        ~frame_allocator();

        [[nodiscard]] pointer allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t));
        void deallocate(pointer, std::size_t, std::size_t = alignof(std::max_align_t));
        bool is_equal(const memory_resource& other) const noexcept;

        void reset(); //Use with caution;

    private:

        std::vector<std::byte> m_buffer;
        std::atomic<std::size_t> m_index;
    };

    TST_INLINE frame_allocator::frame_allocator(std::size_t size) : std::pmr::memory_resource(), m_buffer(size), m_index{0} {
        
    }

    TST_INLINE frame_allocator::~frame_allocator() {
    
    }

    TST_INLINE frame_allocator::pointer frame_allocator::allocate(std::size_t bytes, std::size_t alignment) {
    
    }

    TST_INLINE void frame_allocator::deallocate(frame_allocator::pointer, std::size_t, std::size_t) {
        return;
    }

    TST_INLINE bool frame_allocator::is_equal(const memory_resource& other) const noexcept {
        return this == &other;
    }

    TST_INLINE void frame_allocator::reset() {
        m_index.store(0, std::memory_order_release);
    }

} // namespace core
} // namespace tst