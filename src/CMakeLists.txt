set(${TEMPEST_CODE}
	assert.h
	platform.h
	macros.h
	spinlock.h
	container/queue.h
	memory/frame_allocator.h
	numeric/random.h
	time/timer.h
	util/variant.h
	util/bitpack.h
)

add_library(core INTERFACE)
add_library(tst::core ALIAS core)

target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(core INTERFACE ${TEMPEST_CODE})

source_group("core" FILES ${TEMPEST_CODE})

target_link_libraries(core INTERFACE fmt::fmt)

if(UNIX)
	find_package(Threads)
	target_link_libraries(core INTERFACE ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)