#include "../include/File_Handler.hpp"

File_Handler::File_Handler(const std::string& filepath)
    : filepath_{ filepath }, error_msg_{""}
{}

std::string File_Handler::get_path() const
{
    return filepath_;
}   

std::string File_Handler::what() const
{
    return error_msg_;
}

std::vector<Edge> File_Handler::load_from_file()
{
    std::ifstream in_file;
    in_file.exceptions(std::ifstream::failbit);
    
    std::vector<Edge> out;
    try 
    { 
        in_file.open(filepath_);
        out = load_data(in_file);
        in_file.close();
    }   
    catch(const std::ios_base::failure&)
    {
        error_msg_ = "Error when opening a file.";
        throw;
    }
    catch(const std::invalid_argument&)
    {
        error_msg_ = "Error when parsing data from a file.";
        throw std::ios_base::failure("Error when trying to load data.");
    }
    return out;
}

void File_Handler::save_to_file()
{
    
}

std::vector<Edge> File_Handler::load_data(std::ifstream& in_file)
{
    auto output{ std::vector<Edge>() };
    auto line{ std::string() };
    try
    {
        while(!in_file.eof())
        {
            std::getline(in_file, line);
            if(line.at(0) == '#' || line.size() < 2)
                continue;
            else
                parse_input(output, line);
        }
    }
    catch(const std::invalid_argument){ throw; }

    return output;
}

void File_Handler::parse_input(std::vector<Edge>& output, std::string line)
{
    int start, end, weight;
    if(line.size() >= 5)
    {
        start = line.at(0) - '0';
        end = line.at(2) - '0';
        weight = line.at(4) - '0';
        output.push_back(Edge(start, end, weight));
    }
    else
        throw std::invalid_argument("Error when reading the file.");
}

std::string File_Handler::prep_filepath(std::string filepath)
{
    return filepath;
}

