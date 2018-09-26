#include "../include/File_Handler.hpp"
#include <iostream>


File_Handler::File_Handler(std::string filepath)
    : filepath_{ filepath }, error_msg_{""}
{}

std::string File_Handler::get_path() const
{
    return filepath_;
}   

std::string File_Handler::get_error() const
{
    return error_msg_;
}

std::vector<Edge> File_Handler::load_from_file()
{
    std::vector<Edge> out;
    
    std::ifstream in_file;
    in_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        in_file.open(filepath_);
        if(in_file.is_open())
        {
            out = load_data(in_file);
            in_file.close();
        }
    }
    catch(const std::ifstream::failure& e)
    {
        error_msg_ = "Could not open the file.";
        return std::vector<Edge>();
    }
    return out;
}

void File_Handler::save_to_file()
{
}

std::vector<Edge> File_Handler::load_data(std::ifstream& in_file)
{
    auto output{ std::vector<Edge>() };
    std::string line;
    try
    {
        while(std::getline(in_file, line))
            parse_input(output, line);
    }
    catch(std::ifstream::failure& )
    {
        if(!in_file.eof())
            error_msg_ = "Error occured while reading the file.";
        
        return output; 
    }
    return output;
}

void File_Handler::parse_input(std::vector<Edge>& output, std::string line)
{
    int start, end, weight;
    if(line.size() > 2)
    {
        if(line.at(0) != '#')
        {
            start = line.at(0) - '0';
            end = line.at(2) - '0';
            weight = line.at(4) - '0';
            output.push_back(Edge(start, end, weight));
        }
    }
}

