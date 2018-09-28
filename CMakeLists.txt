cmake_minimum_required(VERSION 2.8.2)

if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(graphs
        DESCRIPTION "SPT and MST algos"
        LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(HEADERS
	${CMAKE_SOURCE_DIR}/include/Adjacency_List.hpp
	${CMAKE_SOURCE_DIR}/include/Adjacency_Matrix.hpp
	${CMAKE_SOURCE_DIR}/include/Node.hpp
	${CMAKE_SOURCE_DIR}/include/File_Handler.hpp
	${CMAKE_SOURCE_DIR}/include/Edge.hpp)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Adjacency_Matrix.cpp
    ${CMAKE_SOURCE_DIR}/src/Adjacency_List.cpp
    ${CMAKE_SOURCE_DIR}/src/Node.cpp
    ${CMAKE_SOURCE_DIR}/src/File_Handler.cpp
    ${CMAKE_SOURCE_DIR}/src/Edge.cpp)

add_executable(graphs ${SOURCES} ${HEADERS})

# Pull and install gtest.
include(${CMAKE_SOURCE_DIR}/cmake/gtest_install.cmake)

set(PROJECT_TEST_NAME graphs_test)

add_executable(${PROJECT_TEST_NAME})

target_sources(${PROJECT_TEST_NAME}
  PRIVATE  
    "${CMAKE_SOURCE_DIR}/test/Adjacency_Matrix_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/Adjacency_List_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/SPT_Matrix_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/SPT_List_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/File_Handler_test.cpp"
    "${CMAKE_SOURCE_DIR}/src/Adjacency_Matrix.cpp"
    "${CMAKE_SOURCE_DIR}/src/Adjacency_List.cpp"
    "${CMAKE_SOURCE_DIR}/src/File_Handler.cpp"
    "${CMAKE_SOURCE_DIR}/src/Edge.cpp"
    "${CMAKE_SOURCE_DIR}/src/Node.cpp")

target_include_directories(${PROJECT_TEST_NAME} 
  PRIVATE ${GTEST_INCLUDE_DIRS}
  PRIVATE "./include")

target_link_libraries(${PROJECT_TEST_NAME} gtest_main)
