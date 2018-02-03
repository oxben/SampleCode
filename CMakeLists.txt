cmake_minimum_required(VERSION 3.5)
project("Sample Code")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

message("---------------------------------------------------------------------")
message("Current Settings:\n")
message("CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})
message("  (Release|Debug)\n")
message("CMAKE_VERBOSE_MAKEFILE=" ${CMAKE_VERBOSE_MAKEFILE})
message("  (True|False)\n")
message("---------------------------------------------------------------------")

add_subdirectory(c)

