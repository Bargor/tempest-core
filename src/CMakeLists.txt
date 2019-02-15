# This file is part of Tempest-core project
# Author: Karol Kontny

set(CORE_HDRS
	core.h
	assert.h
	platform.h
	macros.h
	common/position.h
	atomic/spinlock.h
	container/queue.h
	memory/frame_allocator.h
	numeric/random.h
	time/timer.h
	util/variant.h
)

add_library(core INTERFACE)
add_library(tst::core ALIAS core)

target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(core INTERFACE ${CORE_HDRS})

source_group("core" FILES ${CORE_HDRS})

target_link_libraries(core INTERFACE fmt::fmt)

if(UNIX)
	find_package(Threads)
	target_link_libraries(core INTERFACE ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)