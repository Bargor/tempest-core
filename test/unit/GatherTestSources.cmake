# This file is part of Tempest-core project
# Author: Karol Kontny

set(TEST_CODE ${TEST_CODE} ${CMAKE_CURRENT_SOURCE_DIR}/container/queue_test.cpp)
list(APPEND TEST_CODE ${CMAKE_CURRENT_SOURCE_DIR}/memory/frame_allocator_test.cpp)
list(APPEND TEST_CODE ${CMAKE_CURRENT_SOURCE_DIR}/numeric/random_test.cpp)
list(APPEND TEST_CODE ${CMAKE_CURRENT_SOURCE_DIR}/time/timer_test.cpp)
list(APPEND TEST_CODE ${CMAKE_CURRENT_SOURCE_DIR}/util/bitpack_test.cpp)

set(TEST_CODE ${TEST_CODE} PARENT_SCOPE)