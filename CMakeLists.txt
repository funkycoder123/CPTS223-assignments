cmake_minimum_required(VERSION 3.16)
project(MA1)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(ma1
    main.cpp
    testQueue.cpp
)
