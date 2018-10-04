#pragma once

#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <string>

#include "../include/edge.hpp"

class Adjacency_Matrix{

    using pair_p_queue = std::priority_queue<std::pair<int, int>>;
	using edge_p_queue = std::priority_queue < Edge, std::vector<Edge>, Edge::compare >;
    using pair_vector = std::vector<std::pair<int, int>>;

public:
    Adjacency_Matrix() = delete;
    Adjacency_Matrix(std::vector<std::vector<int>> input);
    Adjacency_Matrix(const std::vector<Edge>& data);

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    const std::vector<int>& operator[](const int index) const;

    int get_size() const;
    std::string to_string() const;

    pair_vector dijkstra(const int start_v);
	pair_vector bellman_ford(const int start_v);
    std::vector<Edge> prim(const int start_v);

private:
    std::vector<std::vector<int>> a_matrix_;

    int find_highest_vertex(const std::vector<Edge>& data) const;
    void fill_w_data(std::vector<std::vector<int>>& empty_mat, const std::vector<Edge>& data);

    bool pre_dijkstra_checks();
    bool negative_weights();
    void dijkstra(pair_vector& cost_prev, const int start_v);
	void dijkstra_relaxation(pair_p_queue& pq, pair_vector& cost_prev);
    std::vector<int> get_neighbours(const int vertex) const;
    void init_costs(pair_vector& cost_prev, const int start_v);
    bool update_cost(pair_vector& cost_prev, const int source, const int neighbour);

	void bellman_ford(std::deque<int>& vertex_q, pair_vector& cost_prev);
	void bf_relaxation(std::deque<int>& vertex_q, pair_vector& cost_prev);
	void slf_push(std::deque<int> &vertex_q, const int neighbour);

    void prim(std::vector<Edge>& tree, std::vector<bool>& visited);
    void remove_loops();
    void update_edge_queue(edge_p_queue& edge_heap, const std::vector<bool>& visited);
	void add_to_queue(const unsigned index, edge_p_queue& edge_heap, const std::vector<bool>& visited);
    void add_reverse_edges(std::vector<Edge>& tree);
};