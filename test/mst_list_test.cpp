#include <gtest/gtest.h>

#include "../include/adjacency_list.hpp"
#include "../include/file_handler.hpp"

TEST(Prim_List, undirected_no_loops)
{
	auto handler{ File_Handler("../data/undir1.txt") };
	auto test_list{ Adjacency_List(handler.load_from_file()) };

	auto expected_data{ std::vector<std::list<Node>>{
        { Node(4, 1) },
        { Node(2, 2), Node(4, 1) },
        { Node(1, 2), Node(3, 1) },
        { Node(2, 1) },
        { Node(0, 1), Node(1, 1) }
        } };
	auto expected{ Adjacency_List(expected_data) };
	auto actual{ Adjacency_List(test_list.prim(0)) };

	EXPECT_EQ(expected, actual);
}

TEST(Prim_List, undirected_loops)
{
	auto handler{ File_Handler("../data/undir3.txt") };
	auto test_list{ Adjacency_List(handler.load_from_file()) };

	auto expected_data{ std::vector<std::list<Node>> {
        { Node(1, 2) ,Node(4, 1) },
        { Node(0, 2) },
        { Node(3, 1) },
        { Node(4, 4), Node(2, 1) },
        { Node(3, 4), Node(0, 1) }
	} };
	auto expected{ Adjacency_List(expected_data) };
	auto actual{ Adjacency_List(test_list.prim(0)) };

	EXPECT_EQ(expected, actual);
}

TEST(Prim_List, undirected_multigraph)
{
    auto handler{ File_Handler("../data/undir4.txt") };
    auto test_list{ Adjacency_List(handler.load_from_file()) };

    auto expected_data{ std::vector<std::list<Node>>{
        { Node(4, 1), Node(1, 2) },
        { Node(0, 2) },
        { Node(3, 1) },
        { Node(4, 1), Node(2, 1)},
        { Node(0, 1), Node(3, 1)}
    } };
    auto expected{ Adjacency_List(expected_data) };
    auto actual{ Adjacency_List(test_list.prim(0)) };

    EXPECT_EQ(expected, actual);
}
