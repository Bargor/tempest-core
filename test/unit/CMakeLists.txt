# This file is part of Tempest-core project
# Author: Karol Kontny

enable_testing()

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

set(TEST_SRCS 
    test_runner.cpp
	container/queue_test.cpp
	memory/frame_allocator_test.cpp
	numeric/random_test.cpp
	time/timer_test.cpp
)

source_group("tests" FILES ${TEST_SRCS})

include(${PROJECT_SOURCE_DIR}/cmake/TstAddLibrary.cmake)

tst_add_executable (core_test "" "${TEST_SRCS}")
add_test(NAME tst.core_unit_test COMMAND core_test)

target_link_libraries(core_test PRIVATE tst::core gmock)

if(UNIX)
	target_link_libraries(core_test PRIVATE gtest)
endif(UNIX)
