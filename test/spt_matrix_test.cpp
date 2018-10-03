#include <gtest/gtest.h>
#include <climits>

#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

TEST(Dijkstra_Matrix, empty)
{
    auto input{ std::vector<std::vector<int>>()};
    auto test_matrix{ Adjacency_Matrix(input) };

	auto expected{ std::vector<std::pair<int,int>>() };
	auto actual{ test_matrix.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_Matrix, one_edge_loop)
{
    auto input{ std::vector<std::vector<int>>( {1} ) };
    auto test_matrix{ Adjacency_Matrix(input) };

    auto expected{std::vector<std::pair<int,int>>{{0, 0}}};
	auto actual{ test_matrix.dijkstra(0) };

    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_Matrix, file_undir1)
{   
    auto handler{ File_Handler("../data/undir1.txt") };
    auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };

	auto expected{ std::vector<std::pair<int, int>> 
			{{0, 0}, {2, 4}, {4, 1}, {5, 2}, {1, 0}}};

    auto actual{ test_matrix.dijkstra(0) };
    
    EXPECT_EQ(expected, actual);
}

TEST(Dijkstra_Matrix, file_directed2)
{
	auto handler{ File_Handler("../data/directed2.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };

	auto expected{ std::vector<std::pair<int, int>>
			{{0, 0}, {4, 3}, {4, 3}, {3, 0}, {INT_MAX, INT_MAX}}};

	auto actual{ test_matrix.dijkstra(0) };

	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, empty)
{
	auto test_matrix{ Adjacency_Matrix(std::vector<std::vector<int>>()) };
	
	auto expected{ std::vector<std::pair<int,int>>() };
	auto actual{ test_matrix.bellman_ford(0) };
	
	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, one_edge_loop)
{
	auto input{ std::vector<std::vector<int>>{1} };
	auto test_matrix{ Adjacency_Matrix(input) };

	auto expected{ std::vector<std::pair<int,int>>() };
	auto actual{ test_matrix.bellman_ford(0) };

	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, file_undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };

	auto expected{ std::vector<std::pair<int,int>>
			{ {0, 0}, {2, 4}, {4, 1}, {5, 2}, {1, 0} }};
	
	auto actual{ test_matrix.bellman_ford(0) };

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, file_directed2)
{
	auto handler{ File_Handler("../data/directed2.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
	std::vector<std::pair<int, int>> actual{ test_matrix.dijkstra(0) };

	auto expected{ std::vector<std::pair<int, int>>
			{{0, 0}, {4, 3}, {4, 3}, {3, 0}, {INT_MAX, INT_MAX}}};

	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, negative_cycle)
{
    auto handler{ File_Handler("../data/directed1.txt") };
    auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
    
	auto expected{ std::vector<std::pair<int, int>>() };
	auto actual{ test_matrix.bellman_ford(0) };

    EXPECT_EQ(expected, actual);
}