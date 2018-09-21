#pragma once

#include <string>
#include "Adjacency_Matrix.hpp"
#include "Adjacency_List.hpp"

class File_Handler{

public:

    File_Handler() = delete;
    File_Handler(Adjacency_Matrix& matrix, const std::string& filepath);
    File_Handler(Adjacency_List& list, const std::string& filepath);

    std::string get_path() const;

    void load_from_file();
    void save_to_file();

private:

    Adjacency_Matrix* matrix_;
    Adjacency_List* list_;

    std::string filepath_;

    std::string prep_filepath(std::string filepath);
};