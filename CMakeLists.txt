cmake_minimum_required(VERSION 2.8.2)

if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(graphs
        DESCRIPTION "SPT and MST algos"
        LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(HEADERS
	${CMAKE_SOURCE_DIR}/include/adjacency_list.hpp
	${CMAKE_SOURCE_DIR}/include/adjacency_matrix.hpp
	${CMAKE_SOURCE_DIR}/include/node.hpp
	${CMAKE_SOURCE_DIR}/include/file_handler.hpp
	${CMAKE_SOURCE_DIR}/include/edge.hpp)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/adjacency_matrix.cpp
    ${CMAKE_SOURCE_DIR}/src/adjacency_list.cpp
    ${CMAKE_SOURCE_DIR}/src/node.cpp
    ${CMAKE_SOURCE_DIR}/src/file_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/edge.cpp)

add_executable(graphs ${SOURCES} ${HEADERS})

# Pull and install gtest.
include(${CMAKE_SOURCE_DIR}/cmake/gtest_install.cmake)

set(PROJECT_TEST_NAME graphs_test)

add_executable(${PROJECT_TEST_NAME})

target_sources(${PROJECT_TEST_NAME}
  PRIVATE  
    "${CMAKE_SOURCE_DIR}/test/adjacency_matrix_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/adjacency_list_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/spt_matrix_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/spt_list_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/mst_matrix_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/mst_list_test.cpp"
    "${CMAKE_SOURCE_DIR}/test/file_handler_test.cpp"
    "${CMAKE_SOURCE_DIR}/src/adjacency_matrix.cpp"
    "${CMAKE_SOURCE_DIR}/src/adjacency_list.cpp"
    "${CMAKE_SOURCE_DIR}/src/file_handler.cpp"
    "${CMAKE_SOURCE_DIR}/src/edge.cpp"
    "${CMAKE_SOURCE_DIR}/src/node.cpp")

target_include_directories(${PROJECT_TEST_NAME} 
  PRIVATE ${GTEST_INCLUDE_DIRS}
  PRIVATE "./include")

target_link_libraries(${PROJECT_TEST_NAME} gtest_main)
