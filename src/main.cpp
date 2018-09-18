#include "../include/Adjacency_Matrix.hpp"
#include <iostream>
int main()
{
    std::cout << "XDD\n";
    auto out{ std::vector<std::vector<int>> (3, std::vector<int>(3)) };
    out.at(0).at(1) = 1;
    out.at(1).at(0) = 1;
    out.at(0).at(2) = 3;
    out.at(2).at(0) = 3;
    out.at(1).at(2) = 1;
    out.at(2).at(1) = 1;

    Adjacency_Matrix matrix{ Adjacency_Matrix(out) };

    auto output{ matrix.dijkstra(0) };
    return 0;
}
