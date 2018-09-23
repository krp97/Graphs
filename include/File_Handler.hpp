#pragma once

#include <string>
#include <fstream>

#include "Adjacency_Matrix.hpp"
#include "Adjacency_List.hpp"
#include "Edge.hpp"

class File_Handler{

public:

    File_Handler() = delete;
    File_Handler(Adjacency_Matrix& matrix, const std::string& filepath);
    File_Handler(Adjacency_List& list, const std::string& filepath);

    std::string get_path() const;

    bool load_from_file();
    void save_to_file();

private:

    Adjacency_Matrix* matrix_;
    Adjacency_List* list_;

    std::string filepath_;
    std::string error_msg_;

    std::vector<Edge> load_data(std::ifstream& in_file);
    void parse_input(std::vector<Edge>& output, std::string line);
    void build_matrix(std::vector<Edge>& data);
    void build_list(std::vector<Edge>& data);
    
    std::string prep_filepath(std::string filepath);
};