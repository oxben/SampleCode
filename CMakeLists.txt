cmake_minimum_required(VERSION 2.8)
project("Sample Code")

# Avoid having empty buildtype
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

message(STATUS "--------------------------------------------------------------")
message(STATUS "Current Settings:")
message(STATUS)
message(STATUS "CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})
message(STATUS "  (Release|Debug)")
message(STATUS "CMAKE_VERBOSE_MAKEFILE=" ${CMAKE_VERBOSE_MAKEFILE})
message(STATUS "  (True|False)")
message(STATUS "--------------------------------------------------------------")

add_subdirectory(c)
