# This file is part of Tempest-engine-GL project
# Author: Karol Kontny

cmake_minimum_required(VERSION 3.11)

project (Tempest-core CXX)

# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")

#Get build number
execute_process(COMMAND git -C ${CMAKE_SOURCE_DIR} rev-parse --short HEAD OUTPUT_VARIABLE VERSION_REVISION)

message(${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}:${VERSION_REVISION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_THREAD_SANITIZER "Run tests with thread sanitizer on Linux" OFF)
option(BUILD_ADDRESS_SANITIZER "Run tests with thread sanitizer on Linux" OFF)
option(BUILD_MEMORY_SANITIZER "Run tests with thread sanitizer on Linux" OFF)
option(BUILD_LEAK_SANITIZER "Run tests with thread sanitizer on Linux" OFF)

#Compiler specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	#General Win compile options
	message("Visual Studio compiler")
	set(TEMPEST_COMPILE_OPTIONS /W4 /WX /MP /std:c++latest /experimental:module)
	set(TEMPEST_COMPILE_DEFINITIONS NOMINMAX)
	set(DEBUG_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} /MDd)
	set(RELEASE_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} /Oi /MD /GL /arch:SSE2)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} /Oi /MD /arch:SSE2)
	#Win linker options
	set(TEMPEST_LINK_OPTIONS /WX)
	set(DEBUG_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
	set(RELEASE_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS} /LTCG)
	set(RELWITHDEBINFO_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS} /LTCG)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message("GCC compiler")
	set(TEMPEST_COMPILE_OPTIONS -Wall -Werror -W -Wextra -pedantic-errors)
	set(DEBUG_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O0)
	set(RELEASE_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O3 -funsafe-loop-optimizations -m64 -march=core2 -mfpmath=sse)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O3 -funsafe-loop-optimizations -m64 -march=core2 -mfpmath=sse)
	#GCC link options
	set(TEMPEST_LINK_OPTIONS)
	set(DEBUG_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
	set(RELEASE_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
	set(RELWITHDEBINFO_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message("Clang compiler")
	set(TEMPEST_COMPILE_OPTIONS -Wall -Werror -W -Wextra -pedantic-errors -stdlib=libc++)
	set(DEBUG_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O0)
	set(RELEASE_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O3 -m64 -march=core2 -mfpmath=sse)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${TEMPEST_COMPILE_OPTIONS} -O3 -m64 -march=core2 -mfpmath=sse)
	#Clang link options
	set(TEMPEST_LINK_OPTIONS "-lc++abi -lc++")
	set(DEBUG_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
	set(RELEASE_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
	set(RELWITHDEBINFO_LINK_OPTIONS ${TEMPEST_LINK_OPTIONS})
endif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#General compiler options

set(RELWITHDEBINFO_COMPILE_DEFINITIONS ${TEMPEST_COMPILE_DEFINITIONS} NDEBUG)
set(RELEASE_COMPILE_DEFINITIONS ${TEMPEST_COMPILE_DEFINITIONS} NDEBUG)
set(DEBUG_COMPILE_DEFINITIONS ${TEMPEST_COMPILE_DEFINITIONS})

set(RUNTIME_OUTPUT_PATH ${CMAKE_BINARY_DIR}/exe)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs)
set(ARCHIVE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/exe)

#Build lib

add_subdirectory(libs/fmt)
add_subdirectory(src)

#Build tests

if(WIN32)
	set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
endif(WIN32)
include(CTest)
add_subdirectory(test/unit)
