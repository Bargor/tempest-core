# This file is part of Tempest-core project
# Author: Karol Kontny

set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/core)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/assert)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/platform)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/macros.h)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/container/queue.h)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/memory/stack_allocator.h)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/numeric/random.h)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/time/timer.h)
set(TEMPEST_CODE ${TEMPEST_CODE} ${CMAKE_SOURCE_DIR}/src/util/variant.h)

source_group(TREE ${CMAKE_SOURCE_DIR}/src FILES ${TEMPEST_CODE})

set(TEMPEST_CODE ${TEMPEST_CODE} PARENT_SCOPE)