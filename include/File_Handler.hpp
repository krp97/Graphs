#pragma once

#include <string>
#include <fstream>

#include "Adjacency_Matrix.hpp"
#include "Adjacency_List.hpp"
#include "Edge.hpp"

class File_Handler{

public:

    File_Handler() = delete;
    File_Handler(const std::string& filepath);

    std::string get_path() const;
    std::string what() const;

    std::vector<Edge> load_from_file();
    void save_to_file();


private:

    std::string filepath_;
    std::string error_msg_;

    std::vector<Edge> load_data(std::ifstream& in_file);
    void parse_input(std::vector<Edge>& output, std::string line);
        
    std::string prep_filepath(std::string filepath);
};