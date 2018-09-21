#include <gtest/gtest.h>
#include "../src/Adjacency_Matrix.cpp"

TEST(Operators, compare_same)
{
    auto input_vec{ std::vector<std::vector<int>>(5, std::vector<int>(5)) };
    input_vec.at(0).at(1) = 3;
    input_vec.at(1).at(4) = 1;
    input_vec.at(2).at(1) = 9;
    input_vec.at(3).at(2) = 5;
    auto obj1{ Adjacency_Matrix(input_vec) };
    auto obj2{ Adjacency_Matrix(input_vec) };

    ASSERT_EQ(obj1, obj2);
}

TEST(Operators, compare_different)
{
    auto input_vec1{ std::vector<std::vector<int>>(5, std::vector<int>(5)) };
    input_vec1.at(0).at(1) = 3;
    input_vec1.at(1).at(4) = 1;
    input_vec1.at(2).at(1) = 9;
    input_vec1.at(3).at(2) = 5;
    auto expected{ Adjacency_Matrix(input_vec1) };

    auto input_vec2{input_vec1};
    input_vec2.at(2).at(2) = 8;
    auto actual{Adjacency_Matrix(input_vec2) };
    ASSERT_NE(expected, actual);
}

TEST(Operators, indexing)
{
    auto input_vec{ std::vector<std::vector<int>>(5, std::vector<int>(5)) };
    input_vec.at(0).at(1) = 3;
    input_vec.at(1).at(4) = 1;
    input_vec.at(2).at(1) = 9;
    input_vec.at(3).at(2) = 5;
    auto test_mat{ Adjacency_Matrix(input_vec) };

    ASSERT_EQ(3, test_mat[0][1]);
    ASSERT_EQ(1, test_mat[1][4]);
    ASSERT_EQ(9, test_mat[2][1]);
    ASSERT_EQ(5, test_mat[3][2]);
}