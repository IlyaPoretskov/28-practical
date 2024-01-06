cmake_minimum_required(VERSION 3.26)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(Simulation_of_an_online_restaurant_kitchen main.cpp
        ${MY_INCLUDE_DIR}/kitchen.h
        kitchen.cpp)

target_include_directories(Simulation_of_an_online_restaurant_kitchen PUBLIC ${MY_INCLUDE_DIR})