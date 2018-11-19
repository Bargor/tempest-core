include(${CMAKE_SOURCE_DIR}/GatherSources.cmake)

add_library(core INTERFACE)

target_sources(core INTERFACE ${TEMPEST_CODE})