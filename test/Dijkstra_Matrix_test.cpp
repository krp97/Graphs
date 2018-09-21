#include "../include/Adjacency_Matrix.hpp"
#include <gtest/gtest.h>

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

TEST(Dijkstra_Matrix, one_edge_standard)
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

TEST(Dijkstra_Matrix, five_edges_standard)
{   

    // Change this once you implement file handling.
    auto input{ std::vector<std::vector<int>>(5, std::vector<int>(5)) };
    input.at(0).at(1) = 1;
    input.at(1).at(0) = 1;
    input.at(0).at(4) = 4;
    input.at(4).at(0) = 4;
    input.at(0).at(3) = 7;
    input.at(3).at(0) = 7;
    
    input.at(1).at(2) = 2;
    input.at(2).at(1) = 2;
    input.at(1).at(4) = 7;
    input.at(4).at(1) = 7;
    
    input.at(4).at(2) = 6;
    input.at(2).at(4) = 6;
    input.at(4).at(3) = 1;
    input.at(3).at(4) = 1;
    
    input.at(3).at(2) = 3;
    input.at(2).at(3) = 3;
    auto test_matrix{Adjacency_Matrix(input)};

    auto expected{std::vector<std::pair<int,int>>()};
    expected.push_back(std::pair<int,int>(0,0));
    expected.push_back(std::pair<int,int>(1,0));
    expected.push_back(std::pair<int,int>(3,1));
    expected.push_back(std::pair<int,int>(5,4));
    expected.push_back(std::pair<int,int>(4,0));

    EXPECT_EQ(expected, test_matrix.dijkstra(0));
}

