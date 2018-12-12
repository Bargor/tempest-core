# This file is part of Tempest-core project
# Author: Karol Kontny

set(TEST_CODE queue_test.cpp)

foreach(SOURCE_FILE ${TEST_CODE})
	get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)

	#Compile files and link with objects
	add_executable (${TEST_NAME} ${SOURCE_FILE})
	
	target_compile_definitions(${TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
	target_compile_definitions(${TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
	target_compile_definitions(${TEST_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

	target_compile_options(${TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
	target_compile_options(${TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
	target_compile_options(${TEST_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

	target_link_libraries(${TEST_NAME} PRIVATE fmt::fmt tst::core benchmark)

	#Link with needed libs
	if(UNIX)
		FIND_PACKAGE(Threads)
		target_link_libraries(${TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
	endif(UNIX)

endforeach(SOURCE_FILE)