# This file is part of Tempest-engine-GL project
# Author: Karol Kontny

function(tst_add_library name hdrs srcs)

add_library(${name} STATIC "")

add_library(tst::${name} ALIAS ${name})

set(all_srcs ${hdrs} ${srcs})

source_group(${name} FILES ${all_srcs})

target_sources(${name} PUBLIC ${hdrs} PRIVATE ${srcs})

target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${name} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
target_compile_options(${name} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
target_compile_options(${name} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

target_compile_definitions(${name} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
target_compile_definitions(${name} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
target_compile_definitions(${name} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

set_target_properties(${name} PROPERTIES LINK_FLAGS_DEBUG "${DEBUG_LINK_OPTIONS}" LINK_FLAGS_RELEASE "${RELEASE_LINK_OPTIONS}" LINKER_LANGUAGE CXX)

endfunction()

function(tst_add_executable name hdrs srcs)

add_executable(${name} "")

add_executable(tst::${name} ALIAS ${name})

set(all_srcs ${hdrs} ${srcs})

source_group(${name} FILES ${all_srcs})

target_sources(${name} PUBLIC ${hdrs} PRIVATE ${srcs})

target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${name} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
target_compile_options(${name} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
target_compile_options(${name} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

target_compile_definitions(${name} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
target_compile_definitions(${name} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
target_compile_definitions(${name} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

set_target_properties(${name} PROPERTIES LINK_FLAGS_DEBUG "${DEBUG_LINK_OPTIONS}" LINK_FLAGS_RELEASE "${RELEASE_LINK_OPTIONS}" LINKER_LANGUAGE CXX)

endfunction()
