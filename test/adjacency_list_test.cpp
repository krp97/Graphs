#include <gtest/gtest.h>
#include "../include/adjacency_list.hpp"
#include "../include/file_handler.hpp"
#include "../include/edge.hpp"

TEST(A_List, compare_same)
{
    auto list1{ std::vector<std::list<Node>>{
        { Node(4, 5), Node(3, 1)} } };
    auto list2{ std::vector<std::list<Node>>{
        { Node(4, 5), Node(3, 1) } }};
    
    Adjacency_List test_list1{ Adjacency_List(list1) };
    Adjacency_List test_list2{ Adjacency_List(list2) };

    ASSERT_EQ(test_list1, test_list2); 
}

TEST(A_List, compare_diff)
{
    auto list_vec1{ std::vector<std::list<Node>>{
        { Node(4, 5), Node(3, 1) }}};
    auto list_vec2{ std::vector<std::list<Node>>{ 
        { Node(3, 6), Node(9, 1) }}};

    Adjacency_List test_list1{ Adjacency_List(list_vec1) };
    Adjacency_List test_list2{ Adjacency_List(list_vec2) };

    ASSERT_NE(test_list1, test_list2);
}

TEST(A_List, indexing)
{
    auto input_list{ std::list<Node>{ Node(2, 3), Node(3, 1) }};
    auto list_vec{ std::vector<std::list<Node>>{ input_list }};

    Adjacency_List test_list{ Adjacency_List(list_vec) };

    ASSERT_EQ(input_list, test_list[0]);
}

TEST(A_List, init_w_file_data)
{
    auto handler{ File_Handler("../test/test_file.txt") };
    auto output{ handler.load_from_file() };
    
    auto exp_input{ std::vector<std::list<Node>>(10, std::list<Node>()) };
    exp_input.at(1).push_back(Node(2, 5));
    exp_input.at(4).push_back(Node(3, 1));
    exp_input.at(9).push_back(Node(8, 1));
    exp_input.at(4).push_back(Node(5, 6));

    auto expected{ Adjacency_List(exp_input) };
    auto actual{ Adjacency_List(output) };

    EXPECT_EQ(expected, actual);
}