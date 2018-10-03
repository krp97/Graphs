#include <gtest/gtest.h>

#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

TEST(Prim_Matrix, file_undir1)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_matrix{ Adjacency_Matrix(handler.load_from_file()) };
	
	auto expected_data{ std::vector<std::vector<int>> {
		{0, 0, 0, 0, 1},
		{0, 0, 2, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0}
	} };
	auto expected{ Adjacency_Matrix(expected_data) };
	auto actual{ Adjacency_Matrix(test_matrix.prim(0)) };

	EXPECT_EQ(expected, actual);
}
