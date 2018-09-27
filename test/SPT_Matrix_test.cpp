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

TEST(Dijkstra_Matrix, one_edge)
{
    auto input{ std::vector<std::vector<int>>(2, std::vector<int>(2)) };
    input.at(0).at(1) = 2;
    input.at(1).at(0) = 2;
    auto test_matrix{ Adjacency_Matrix(input) };

    auto expected{ std::vector<std::pair<int,int>>()};
    expected.push_back(std::pair<int,int>(0,0));
    expected.push_back(std::pair<int,int>(2,0));

    EXPECT_EQ(expected, test_matrix.dijkstra(0));
}

TEST(Dijkstra_Matrix, undir1_case)
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

