// This file is part of Tempest-core project
// Author: Karol Kontny

#include <variant>
#include <cstdint>

#pragma once

namespace tst
{
namespace core
{

template<typename VariantType, typename T, std::size_t index = 0>
constexpr std::size_t variant_index() {
    if constexpr (index == std::variant_size_v<VariantType>) {
        static_assert(index < std::variant_size_v<VariantType>, "Wrong variant type");
        return index;
    } else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return index;
    } else {
        return variant_index<VariantType, T, index + 1>();
    }
}

}
}