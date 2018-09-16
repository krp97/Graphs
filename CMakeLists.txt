
project(Graphs
        DESCRIPTION "SPT and MST algos"
        LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12.1)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_BUILD_TYPE Debug)

add_executable(Graphs ${SOURCES})

target_include_directories(Graphs PUBLIC "./include")
target_sources(Graphs 
        PUBLIC
            "./src/main.cpp"
            "./src/Adjacency_Matrix.cpp")
