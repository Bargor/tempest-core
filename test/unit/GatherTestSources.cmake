# This file is part of Tempest-core project
# Author: Karol Kontny

set(TEMPEST_CODE ${TEST_CODE} ${CMAKE_CURRENT_SOURCE_DIR}/container/queue_test.cpp)
set(TEMPEST_CODE ${TEST_CODE} ${CMAKE_CURRENT_SOURCE_DIR}/memory/frame_allocator_test.cpp)
set(TEMPEST_CODE ${TEST_CODE} ${CMAKE_CURRENT_SOURCE_DIR}/numeric/random_test.cpp)
set(TEMPEST_CODE ${TEST_CODE} ${CMAKE_CURRENT_SOURCE_DIR}/time/timer_test.cpp)

set(TEMPEST_CODE ${TEMPEST_CODE} PARENT_SCOPE)