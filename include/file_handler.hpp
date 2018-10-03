#pragma once

#include <string>
#include <fstream>

#include "adjacency_matrix.hpp"
#include "adjacency_list.hpp"
#include "edge.hpp"

class File_Handler{

public:

    File_Handler() = delete;
    File_Handler(std::string filepath);

    std::string get_path() const;
    std::string get_error() const;

    std::vector<Edge> load_from_file();
    void save_to_file();

    std::string error_msg_;
private:

    std::string filepath_;
    

    std::vector<Edge> load_data(std::ifstream& in_file);
    void parse_input(std::vector<Edge>& output, std::string line);
};