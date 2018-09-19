#include <gtest/gtest.h>
#include "../src/Adjacency_Matrix.cpp"

TEST(Operators, compare_same)
{
    auto expected{ Adjacency_Matrix(3) };
    expected[0][1] = 1;
    expected[1][0] = 1;
    expected[0][2] = 3;
    expected[2][0] = 3;
    expected[1][2] = 1;
    expected[2][1] = 1;

    auto input_vec{ std::vector<std::vector<int>> (3, std::vector<int>(3))};
    input_vec.at(0).at(1) = 1;
    input_vec.at(1).at(0) = 1;
    input_vec.at(0).at(2) = 3;
    input_vec.at(2).at(0) = 3;
    input_vec.at(1).at(2) = 1;
    input_vec.at(2).at(1) = 1;
    auto actual{ Adjacency_Matrix(input_vec) };

    EXPECT_EQ(expected, actual);
}

TEST(Operators, compare_different)
{
    auto expected{ Adjacency_Matrix(5) };
    auto actual{Adjacency_Matrix(6) };
    EXPECT_NE(expected, actual);
}

TEST(Init, fixed_size_zeros)
{
    
}

TEST(Init, with_data)
{

}

TEST(Operators, indexing)
{

}