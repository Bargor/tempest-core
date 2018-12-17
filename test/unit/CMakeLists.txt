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

#Find test files
#TODO Make it better
include(GatherTestSources.cmake)

set(TEST_RUNNER test_runner.cpp)
set(TEST_SRCS ${TEST_RUNNER} ${TEST_CODE})

message(${TEST_CODE})

source_group("tests" FILES ${TEST_SRCS})

add_executable (core_test ${TEST_SRCS})
add_test(NAME tst.core_unit_test COMMAND core_test)

target_compile_definitions(core_test PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
target_compile_definitions(core_test PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
target_compile_definitions(core_test PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

target_compile_options(core_test PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
target_compile_options(core_test PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
target_compile_options(core_test PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

set_target_properties(core_test PROPERTIES LINK_FLAGS_RELEASE "${RELEASE_LINK_OPTIONS}" LINK_FLAGS_DEBUG "${DEBUG_LINK_OPTIONS}" LINKER_LANGUAGE CXX)

target_link_libraries(core_test PRIVATE core gmock)

if(UNIX)
	target_link_libraries(core_test PRIVATE gtest)
endif(UNIX)
