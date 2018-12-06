include(${CMAKE_SOURCE_DIR}/GatherSources.cmake)

add_library(core INTERFACE)

add_library(tst::core ALIAS core)

target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(core INTERFACE ${TEMPEST_CODE})

source_group("core" FILES ${TEMPEST_CODE})

target_link_libraries(core INTERFACE fmt::fmt)

if(UNIX)
	find_package(Threads)
	target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)
if(WIN32)
	target_link_libraries(core)
endif(WIN32)