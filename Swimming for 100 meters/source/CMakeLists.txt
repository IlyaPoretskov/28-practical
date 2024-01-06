cmake_minimum_required(VERSION 3.26)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(Swimming_for_100_meters main.cpp
        ${MY_INCLUDE_DIR}/swimmer.h
        swimmer.cpp)

target_include_directories(Swimming_for_100_meters PUBLIC ${MY_INCLUDE_DIR})