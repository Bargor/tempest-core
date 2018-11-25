// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

namespace tst {
namespace core {

    template<typename T>
    class stack_allocator {
    public:
        using value_type = T;

        [[nodiscard]] T* allocate(std::size_t n);

    private:
    };

}
}