#include <gtest/gtest.h>

#include "../include/File_Handler.hpp"

TEST(File_Handler, load_fail)
{
    auto handler{ File_Handler("badstring") };
    ASSERT_THROW(handler.load_from_file(), std::ios_base::failure);
}

TEST(File_Handler, load_pass)
{
    auto handler{ File_Handler("/home/desktop/Desktop/Github/Graphs/data/undir1.txt") };
    ASSERT_NO_THROW(handler.load_from_file());
}

TEST(File_Handler, save)
{

}