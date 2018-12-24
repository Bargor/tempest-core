// This file is part of Tempest-core project
// Author: Karol Kontny

#include <type_traits>
#include <cstdint>

#pragma once

namespace tst {
namespace core {

    namespace detail {
        constexpr std::uint32_t byte_size = 8;
    }

    template<typename T>
    constexpr std::size_t bits_size() {
        return sizeof(T) * detail::byte_size;
    }
    
    template<typename FullType, typename HalfType,
             typename = std::enable_if_t<std::is_integral_v<FullType>>,
             typename = std::enable_if_t<std::is_integral_v<HalfType>>>
    HalfType get_high_bits(FullType num) {

        static_assert(sizeof(FullType) == sizeof(HalfType) * 2);

        return static_cast<HalfType>(num >> bits_size<HalfType>());
    }

    template<typename FullType,
             typename HalfType,
             typename = std::enable_if_t<std::is_integral_v<FullType>>,
             typename = std::enable_if_t<std::is_integral_v<HalfType>>>
    HalfType get_low_bits(FullType num) {

        static_assert(sizeof(FullType) == sizeof(HalfType) * 2);

        FullType mask = std::numeric_limits<HalfType>::max();
        return static_cast<HalfType>(mask & num);
    }

    template<typename FullType,
             typename HalfType,
             typename = std::enable_if_t<std::is_integral_v<FullType>>,
             typename = std::enable_if_t<std::is_integral_v<HalfType>>>
    FullType combine(HalfType high, HalfType low) {
        static_assert(sizeof(FullType) == sizeof(HalfType) * 2);

        return ((static_cast<FullType>(high)) << bits_size<HalfType>()) | (static_cast<FullType>(low));
    }

}
}