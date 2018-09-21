#pragma once

#include <vector>
#include <queue>

class Adjacency_Matrix{

    using pair_pqueue = std::priority_queue<std::pair<int,int>>;
    using pair_vector = std::vector<std::pair<int,int>>;

public:
    Adjacency_Matrix() = delete;
    Adjacency_Matrix(std::vector<std::vector<int>> matrix);

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    const std::vector<int>& operator[](const int index) const;

    int get_size() const;

    pair_vector dijkstra(const int start_v);

private:

    // Future note:
    // If load and save to file is not implemented by the end of the project,
    // this attribute(same with the list) has to be changed to a ref to const.
    std::vector<std::vector<int>> a_matrix_;
    Adjacency_Matrix(const int size);   // Only used for initializing with files.

    bool pre_dijkstra_checks();
    bool negative_weights();
    bool lone_nodes();
    bool undirected();
    void dijkstra(pair_pqueue& pq, pair_vector& cost_prev);
    std::vector<int> extract_neighbours(const int vertex);
    void init_costs(pair_vector& cost_prev, const int start_v);
    bool update_cost(pair_vector& cost_prev, const int source, const int neighbour);
};