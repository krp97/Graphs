#pragma once

#include <vector>
class Adjacency_Matrix{

public:

    Adjacency_Matrix(std::vector<std::vector<int>>& matrix);
    Adjacency_Matrix(const int size);

    bool operator==(const Adjacency_Matrix& rhs);
    std::vector<int>& operator[](const int index);

private:
    std::vector<std::vector<int>> a_matrix_;

};