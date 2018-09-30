#include <gtest/gtest.h>
#include "../include/Adjacency_Matrix.hpp"
#include "../include/File_Handler.hpp"

TEST(Dijkstra_Matrix, empty)
{
    auto input{ std::vector<std::vector<int>>(0, std::vector<int>(0))};
    auto expected{ std::vector<std::pair<int,int>>() };
    auto test_matrix{ Adjacency_Matrix(input) };

    EXPECT_EQ(expected, test_matrix.dijkstra(0));
}

TEST(Dijkstra_Matrix, one_edge_loop)
{
    auto input{ std::vector<std::vector<int>>(1, std::vector<int>(1)) };
    input.at(0).at(0) = 1;
    auto test_matrix{ Adjacency_Matrix(input) };

    auto expected{std::vector<std::pair<int,int>>()};
    expected.push_back(std::pair<int,int>(0,0));

    EXPECT_EQ(expected, test_matrix.dijkstra(0));
}

TEST(Dijkstra_Matrix, undir1)
{   
    auto handler{ File_Handler("../data/undir1.txt") };
    auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
    std::vector<std::pair<int,int>> actual{ test_matrix.dijkstra(0) };
    
    auto expected{ std::vector<std::pair<int,int>> (5, std::pair<int,int>()) };
    expected.at(0) = std::pair<int,int>(0, 0);
    expected.at(4) = std::pair<int,int>(1, 0);
    expected.at(1) = std::pair<int,int>(2, 4);
    expected.at(2) = std::pair<int,int>(4, 1);
    expected.at(3) = std::pair<int,int>(5, 2);

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, empty)
{
	auto test_matrix{ Adjacency_Matrix(std::vector<std::vector<int>>()) };
	std::vector<std::pair<int, int>> actual{ test_matrix.bellman_ford(0) };
	
	auto expected{ std::vector<std::pair<int,int>>() };
	EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, one_edge_loop)
{
	auto input{ std::vector<std::vector<int>>(1, std::vector<int>(1)) };
	input.at(0).at(0) = 1;
	auto test_matrix{ Adjacency_Matrix(input) };

	auto expected{ std::vector<std::pair<int,int>>() };

	EXPECT_EQ(expected, test_matrix.bellman_ford(0));
}

TEST(B_Ford_Matrix, undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
	std::vector<std::pair<int, int>> actual{ test_matrix.bellman_ford(0) };

	auto expected{ std::vector<std::pair<int,int>>(5, std::pair<int,int>()) };
	expected.at(0) = std::pair<int, int>(0, 0);
	expected.at(4) = std::pair<int, int>(1, 0);
	expected.at(1) = std::pair<int, int>(2, 4);
	expected.at(2) = std::pair<int, int>(4, 1);
	expected.at(3) = std::pair<int, int>(5, 2);

    EXPECT_EQ(expected, actual);
}

TEST(B_Ford_Matrix, negative_cycle)
{
    auto handler{ File_Handler("../data/directed1.txt") };
    auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
    std::vector<std::pair<int,int>> actual{ test_matrix.bellman_ford(0) };

    auto expected{ std::vector<std::pair<int, int>>() };
    EXPECT_EQ(expected, actual);
}

TEST(Prim_Matrix, undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
	auto actual{ Adjacency_Matrix(test_matrix.prim(0)) };

	auto expected_input{ std::vector<std::vector<int>> (5, std::vector<int>(5)) };
	expected_input.at(0).at(4) = 1;
	expected_input.at(4).at(1) = 1;
	expected_input.at(1).at(2) = 2;
	expected_input.at(2).at(3) = 1;
	auto expected{ Adjacency_Matrix(expected_input) };
	EXPECT_EQ(expected, actual);
	std::cout << "\n\n\n" << expected.to_string() << "\n\n\n";
	std::cout << actual.to_string() << "\n\n\n";
}
