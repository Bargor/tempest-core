# This file is part of Tempest-core project
# Author: Karol Kontny

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/libs/googletest/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include)

#Find test files
#TODO Make it better
file(GLOB_RECURSE TEST_CODE "*_test.cpp")

set(TEST_RUNNER test_runner.cpp)
set(TEST_SRCS ${TEST_RUNNER} ${TEST_CODE})

source_group("Tests" FILES ${TEST_SRCS})

add_executable (core_test ${TEST_SRCS} ${TEMPEST_CODE})
add_test(NAME unit_test COMMAND core_test)

target_compile_definitions(core_test PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
target_compile_definitions(core_test PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
target_compile_definitions(core_test PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

target_compile_options(core_test PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
target_compile_options(core_test PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
target_compile_options(core_test PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

add_dependencies(core_test gmock fmt)

set_target_properties(core_test PROPERTIES LINK_FLAGS_RELEASE "${RELEASE_LINK_OPTIONS}" LINK_FLAGS_DEBUG 		"${DEBUG_LINK_OPTIONS}" LINKER_LANGUAGE CXX)

if(UNIX)
	FIND_PACKAGE(Threads)
	target_link_libraries(core_test ${LIBRARY_OUTPUT_DIRECTORY}/libfmt.a ${LIBRARY_OUTPUT_DIRECTORY}/libgmock.a ${CMAKE_THREAD_LIBS_INIT} core)
endif(UNIX)
if(WIN32)
	target_link_libraries(core_test debug ${LIBRARY_OUTPUT_DIRECTORY}/Debug/fmtd.lib debug ${LIBRARY_OUTPUT_DIRECTORY}/Debug/gmockd.lib
		optimized ${LIBRARY_OUTPUT_DIRECTORY}/Release/fmt.lib optimized ${LIBRARY_OUTPUT_DIRECTORY}/Release/gmock.lib core)
endif(WIN32)
