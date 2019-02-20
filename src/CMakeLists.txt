# This file is part of Tempest-core project
# Author: Karol Kontny

set(CORE_HDRS
	core.h
	assert.h
	platform.h
	macros.h
	algorithm/algorithm.h
	atomic/spinlock.h
	common/position.h
	container/queue.h
	memory/frame_allocator.h
	numeric/random.h
	time/timer.h
	thread/main_thread.h
	util/variant.h
)

set(CORE_SRCS
	thread/main_thread.cpp
)

include(${PROJECT_SOURCE_DIR}/cmake/TstAddLibrary.cmake)

tst_add_library(core "${CORE_HDRS}" "${CORE_SRCS}")

target_link_libraries(core PUBLIC fmt::fmt)

if(UNIX)
	find_package(Threads)
	target_link_libraries(core PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)