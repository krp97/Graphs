#include "../include/File_Handler.hpp"

File_Handler::File_Handler(Adjacency_Matrix& matrix, const std::string& filepath)
    : matrix_{ &matrix }, list_{ nullptr }, filepath_{ filepath }, error_msg_{""}
{}

File_Handler::File_Handler(Adjacency_List& list, const std::string& filepath)
    : matrix_{ nullptr }, list_{ &list }, filepath_{ filepath }, error_msg_{""}
{}

std::string File_Handler::get_path() const
{
    return filepath_;
}   

bool File_Handler::load_from_file()
{
    std::ifstream in_file;
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
        return false;
    }
    catch(const std::invalid_argument&)
    {
        error_msg_ = "Error when reading from a file.";
        return false;
    }

    if(matrix_)
        build_matrix(out);
    else if(list_)
        build_list(out);

    return true;
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

void File_Handler::build_matrix(std::vector<Edge>& data)
{
    for(auto& edges : data)
    {
        
    }
}

void File_Handler::build_list(std::vector<Edge>& data)
{

}

std::string File_Handler::prep_filepath(std::string filepath)
{

}

