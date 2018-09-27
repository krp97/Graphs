
cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.1)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Graphs
        DESCRIPTION "SPT and MST algos"
        LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

add_executable(Graphs ${SOURCES})
target_sources(Graphs 
        PUBLIC
            "./src/main.cpp"
            "./src/Adjacency_Matrix.cpp"
            "./src/Adjacency_List.cpp"
            "./src/Node.cpp"
            "./src/File_Handler.cpp"
            "./src/Edge.cpp")
target_include_directories(Graphs PRIVATE "./include")