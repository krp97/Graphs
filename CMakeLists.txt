
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
            "./src/Node.cpp"
            "./src/File_Handler.cpp")
target_include_directories(Graphs PRIVATE "./include")

# Test module with GTest
find_package(GTest REQUIRED)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
add_executable(${PROJECT_TEST_NAME} ${SOURCES})

target_sources(${PROJECT_TEST_NAME}
        PUBLIC  
            "./test/Adjacency_Matrix_test.cpp"
            "./test/Dijkstra_Matrix_test.cpp")
target_include_directories(${PROJECT_TEST_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
