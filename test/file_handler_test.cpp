#include <gtest/gtest.h>
#include <climits>

#include "../include/file_handler.hpp"

TEST(File_Handler, load_fail)
{
    auto handler{ File_Handler("badstring") };
    auto expected{ std::vector<Edge>() };
    
    ASSERT_EQ(expected, handler.load_from_file());
    ASSERT_EQ("Could not open the file.", handler.get_error());
}
TEST(File_Handler, load_pass)
{
    auto handler{ File_Handler("../test/test_file.txt") };
    auto expected{ std::vector<Edge>{ 
        Edge(1, 2, 5), Edge(4, 3, 1), Edge(9, 8, 1), Edge(4, 5, 6)} };

    ASSERT_EQ(expected, handler.load_from_file());
    ASSERT_EQ("", handler.get_error());
}