#include <gtest/gtest.h>
#include "../../include/Adjacency_List.hpp"
#include "../../include/File_Handler.hpp"
#include "../../include/Edge.hpp"

TEST(A_List, compare_same)
{
    auto list1{ std::vector<std::list<Node>>(2, std::list<Node>()) };
    auto list2{ std::vector<std::list<Node>>(2, std::list<Node>()) };

    list1.at(0).push_back(Node(4, 5));
    list1.at(1).push_back(Node(3, 1));

    list2.at(0).push_back(Node(4, 5));
    list2.at(1).push_back(Node(3, 1));
    
    Adjacency_List test_list1{ Adjacency_List(list1) };
    Adjacency_List test_list2{ Adjacency_List(list2) };

    ASSERT_EQ(test_list1, test_list2); 
}

TEST(A_List, compare_diff)
{
    auto list_vec1{ std::vector<std::list<Node>>(2, std::list<Node>()) };
    auto list_vec2{ std::vector<std::list<Node>>(3, std::list<Node>()) };

    list_vec1.at(0).push_back(Node(4, 5));
    list_vec1.at(1).push_back(Node(3, 1));

    list_vec2.at(0).push_back(Node(3, 6));
    list_vec2.at(2).push_back(Node(9, 1));

    Adjacency_List test_list1{ Adjacency_List(list_vec1) };
    Adjacency_List test_list2{ Adjacency_List(list_vec2) };

    ASSERT_NE(test_list1, test_list2);
}

TEST(A_List, indexing)
{
    auto list_vec{ std::vector<std::list<Node>>(3, std::list<Node>()) };
    auto input_list{ std::list<Node>() };

    input_list.push_back(Node(2, 3));
    input_list.push_back(Node(3, 1));
    list_vec.at(0) = input_list;

    Adjacency_List test_list{ Adjacency_List(list_vec) };

    ASSERT_EQ(input_list, test_list[0]);
}

TEST(A_List, init_w_file_data)
{
    auto handler{ File_Handler("../test_file.txt") };
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