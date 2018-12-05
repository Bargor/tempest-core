include(${CMAKE_SOURCE_DIR}/GatherSources.cmake)

add_library(core INTERFACE)

target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(core INTERFACE ${TEMPEST_CODE})

source_group("core" FILES ${TEMPEST_CODE})

if(UNIX)
	find_package(Threads)
	target_link_libraries(core INTERFACE ${LIBRARY_OUTPUT_PATH}/libfmt.a ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)
if(WIN32)
	target_link_libraries(core INTERFACE debug ${LIBRARY_OUTPUT_PATH}/Debug/fmt.lib optimized ${LIBRARY_OUTPUT_PATH}/Release/fmt.lib)
endif(WIN32)