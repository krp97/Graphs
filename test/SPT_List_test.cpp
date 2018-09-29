#include <gtest/gtest.h>

#include "../include/Adjacency_List.hpp"
#include "../include/File_Handler.hpp"

TEST(Dijkstra_List, empty)
{
    auto input{ std::vector<std::list<Node>>()};
    auto expected{ std::vector<std::pair<int,int>>() };
    auto test_list{ Adjacency_List(input) };

    EXPECT_EQ(expected, test_list.dijkstra(0));
}

TEST(Dijkstra_List, one_edge_loop)
{
    auto input{ std::vector<std::list<Node>>(1, std::list<Node>()) };
    input.at(0).push_back(Node(0, 1));
    auto test_list{ Adjacency_List(input) };

    auto expected{std::vector<std::pair<int,int>>()};
    expected.push_back(std::pair<int,int>(0,0));

    EXPECT_EQ(expected, test_list.dijkstra(0));
}

TEST(Dijkstra_List, one_edge)
{
    auto input{  std::vector<std::list<Node>>(2, std::list<Node>()) };
    input.at(0).push_back(Node(1, 2));
    input.at(1).push_back(Node(0, 2));
    auto test_list{ Adjacency_List(input) };

    auto expected{ std::vector<std::pair<int,int>>()};
    expected.push_back(std::pair<int,int>(0,0));
    expected.push_back(std::pair<int,int>(2,0));

    EXPECT_EQ(expected, test_list.dijkstra(0));
}

TEST(Dijkstra_List, undir1_case)
{   
    auto handler{ File_Handler("../data/undir1.txt") };
    auto test_list{ Adjacency_List(handler.load_from_file()) };
    std::vector<std::pair<int,int>> actual{ test_list.dijkstra(0) };
    
    auto expected{ std::vector<std::pair<int,int>> (5, std::pair<int,int>()) };
    expected.at(0) = std::pair<int,int>(0, 0);
    expected.at(4) = std::pair<int,int>(1, 0);
    expected.at(1) = std::pair<int,int>(2, 4);
    expected.at(2) = std::pair<int,int>(4, 1);
    expected.at(3) = std::pair<int,int>(5, 2);

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, empty)
{
	auto test_list{ Adjacency_List(std::vector<std::list<Node>>()) };
	std::vector<std::pair<int, int>> actual{ test_list.bellman_ford(0) };

	auto expected{ std::vector<std::pair<int,int>>() };
	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, one_edge_loop)
{
	auto input{ std::vector<std::list<Node>>(1) };
	input.at(0).push_back(Node(0, 1));
	auto test_list{ Adjacency_List(input) };

	auto expected{ std::vector<std::pair<int,int>>() };

	EXPECT_EQ(expected, test_list.bellman_ford(0));
}

TEST(B_Ford_List, undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_list{ Adjacency_List(handler.load_from_file()) };
	std::vector<std::pair<int, int>> actual{ test_list.bellman_ford(0) };

	auto expected{ std::vector<std::pair<int,int>>(5, std::pair<int,int>()) };
	expected.at(0) = std::pair<int, int>(0, 0);
	expected.at(4) = std::pair<int, int>(1, 0);
	expected.at(1) = std::pair<int, int>(2, 4);
	expected.at(2) = std::pair<int, int>(4, 1);
	expected.at(3) = std::pair<int, int>(5, 2);

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_List, negative_cycle)
{
    auto handler{ File_Handler("../data/directed1.txt") };
    auto test_list{ Adjacency_List(handler.load_from_file()) };
    std::vector<std::pair<int,int>> actual{ test_list.bellman_ford(0) };

    auto expected{ std::vector<std::pair<int, int>>() };
    EXPECT_EQ(expected, actual);
}
