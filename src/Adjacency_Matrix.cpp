#include "../include/Adjacency_Matrix.hpp"

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>>& matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const int size)
    : a_matrix_{ std::vector<std::vector<int>>(size) }
{}

std::vector<int>& Adjacency_Matrix::operator[](const int index)
{
    return a_matrix_.at(index);
}

bool Adjacency_Matrix::operator==(const Adjacency_Matrix& rhs)
{
    auto vec_it{ a_matrix_.begin() };
    auto rhs_it{ rhs.a_matrix_.begin() };

    for(; vec_it != a_matrix_.end(); ++vec_it, ++rhs_it)
        if( !std::equal((*vec_it).begin(), (*vec_it).end(), (*rhs_it).begin()) )
            return false;
    
    return true;
}