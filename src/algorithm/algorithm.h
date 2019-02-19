// This file is part of Tempest-core project
// Author: Karol Kontny

#pragma once

#include <algorithm>
#include <platform.h>

// Workaround for GCC

#if TST_COMPILER & TST_COMPILER_GCC

namespace std {
template<class InputIt, class Size, class UnaryFunction>
InputIt for_each_n(InputIt first, Size n, UnaryFunction f) {
    for (Size i = 0; i < n; ++first, (void)++i) {
        f(*first);
    }
    return first;
}
} // namespace std

#endif 


