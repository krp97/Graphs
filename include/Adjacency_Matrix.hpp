#pragma once

#include <vector>
#include <queue>
class Adjacency_Matrix{

    using pair_pqueue = std::priority_queue<std::pair<int,int>>;
    using pair_vector = std::vector<std::pair<int,int>>;

public:
    Adjacency_Matrix(std::vector<std::vector<int>>& matrix);
    Adjacency_Matrix(const int size);

    bool operator==(const Adjacency_Matrix& rhs);
    std::vector<int>& operator[](const int index);
    pair_vector dijkstra(const int start_v);

private:
    std::vector<std::vector<int>> a_matrix_;

    void dijkstra(pair_pqueue& pq, pair_vector& cost_prev);
    std::vector<int> extract_neighbours(const int vertex);
    void init_costs(pair_vector& cost_prev, const int start_v);
    bool update_cost(pair_vector& cost_prev, const int source, const int neighbour);
};