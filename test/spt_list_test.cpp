#include <gtest/gtest.h>

#include "../include/adjacency_list.hpp"
#include "../include/file_handler.hpp"

TEST(Dijkstra_List, empty)
{
    auto input{ std::vector<std::list<Node>>()};
    auto test_list{ Adjacency_List(input) };

    auto expected{ std::vector<std::pair<int,int>>() };
    auto actual{ test_list.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_List, one_edge_loop)
{
    auto input{ std::vector<std::list<Node>>{ {Node(0, 1)} }};
    auto test_list{ Adjacency_List(input) };

    auto expected{std::vector<std::pair<int,int>>{ {0, 0} }};
    auto actual{ test_list.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_List, one_edge)
{
    auto input{  std::vector<std::list<Node>>{
        {Node(1, 2)}, {Node(0, 2)} }};
    auto test_list{ Adjacency_List(input) };

    auto expected{ std::vector<std::pair<int,int>>{
        {0, 0}, {2, 0} }};

    auto actual{ test_list.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_List, undir1_case)
{   
    auto handler{ File_Handler("../data/undir1.txt") };
    auto test_list{ Adjacency_List(handler.load_from_file()) };
    
    auto expected{ std::vector<std::pair<int,int>>{
        {0, 0}, {2, 4}, {4, 1}, {5, 2}, {1, 0} }};

    auto actual{ test_list.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, empty)
{
	auto test_list{ Adjacency_List(std::vector<std::list<Node>>()) };

	auto expected{ std::vector<std::pair<int,int>>() };
    auto actual{ test_list.bellman_ford(0) };

	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, one_edge_loop)
{
	auto input{ std::vector<std::list<Node>>{ {Node(0, 1)} }};
	auto test_list{ Adjacency_List(input) };

	auto expected{ std::vector<std::pair<int,int>>() };
    auto actual{ test_list.bellman_ford(0) };

	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_list{ Adjacency_List(handler.load_from_file()) };

	auto expected{ std::vector<std::pair<int,int>>{ 
        {0, 0}, {2, 4}, {4, 1}, {5, 2}, {1, 0} } };

    auto actual{ test_list.bellman_ford(0) };

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, negative_cycle)
{
    auto handler{ File_Handler("../data/directed1.txt") };
    auto test_list{ Adjacency_List(handler.load_from_file()) };

    auto expected{ std::vector<std::pair<int, int>>() };
    auto actual{ test_list.bellman_ford(0) };
    
    EXPECT_EQ(expected, actual);
}
