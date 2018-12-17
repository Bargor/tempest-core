# This file is part of Tempest-core project
# Author: Karol Kontny

set(TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/core.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/assert.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/platform.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/macros.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/atomic/spinlock.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/container/queue.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/memory/frame_allocator.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/numeric/random.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/time/timer.h)
list(APPEND TEMPEST_CODE ${CMAKE_SOURCE_DIR}/src/util/variant.h)

set(TEMPEST_CODE ${TEMPEST_CODE} PARENT_SCOPE)