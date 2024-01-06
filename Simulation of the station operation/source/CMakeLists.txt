cmake_minimum_required(VERSION 3.26)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(Simulation_of_the_station_operation main.cpp
        ${MY_INCLUDE_DIR}/train.h
        train.cpp)

target_include_directories(Simulation_of_the_station_operation PUBLIC ${MY_INCLUDE_DIR})