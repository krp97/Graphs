#include "../include/File_Handler.hpp"

File_Handler::File_Handler(Adjacency_Matrix& matrix, const std::string& filepath)
    : matrix_{ &matrix }, list_{ nullptr }, filepath_{ filepath }
{}

File_Handler::File_Handler(Adjacency_List& list, const std::string& filepath)
    : matrix_{ nullptr }, list_{ &list }, filepath_{ filepath }
{}

std::string File_Handler::get_path() const
{
    return filepath_;
}   

void File_Handler::load_from_file()
{

}

void File_Handler::save_to_file()
{

}

std::string File_Handler::prep_filepath(std::string filepath)
{}

