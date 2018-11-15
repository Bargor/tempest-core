# This file is part of Tempest-core project
# Author: Karol Kontny

project (Tempest-core CXX)

include(CTest)
enable_testing()

include_directories(${INCLUDE_PATHS})
include_directories(${CMAKE_SOURCE_DIR}/libs/googletest/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include)

message(${LIBRARY_OUTPUT_PATH})

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/googletest ${LIBRARY_OUTPUT_PATH})

link_directories(${LIBRARY_OUTPUT_PATH})

include(${CMAKE_SOURCE_DIR}/GatherSources.cmake)

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

add_dependencies(core_test gmock)

set_target_properties(core_test PROPERTIES LINK_FLAGS_RELEASE "${RELEASE_LINK_OPTIONS}" LINK_FLAGS_DEBUG 		"${DEBUG_LINK_OPTIONS}" LINKER_LANGUAGE CXX)

if(UNIX)
	FIND_PACKAGE(Threads)
	target_link_libraries(core_test ${LIBRARY_OUTPUT_PATH}/libgmock.a)
	target_link_libraries(core_test ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)
if(WIN32)
	target_link_libraries(core_test debug ${LIBRARY_OUTPUT_PATH}/Debug/gmockd.lib
		optimized ${LIBRARY_OUTPUT_PATH}/Release/gmock.lib)
endif(WIN32)
