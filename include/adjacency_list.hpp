#pragma once

#include "node.hpp"
#include "edge.hpp"

#include <list>
#include <vector>
#include <queue>

class Adjacency_List{

    using pair_pqueue = std::priority_queue<std::pair<int,int>>;
    using edge_p_queue = std::priority_queue < Edge, std::vector<Edge>, Edge::compare >;
    using pair_vector = std::vector<std::pair<int,int>>;

public:
    Adjacency_List() = delete;
    Adjacency_List(std::vector<std::list<Node>> list);
    Adjacency_List(std::vector<Edge> file_input);

    bool operator==(const Adjacency_List& rhs) const;
    bool operator!=(const Adjacency_List& rhs) const;
    const std::list<Node>& operator[](const int index) const;

	std::string to_string() const;

    pair_vector dijkstra(const int start_v);
	pair_vector bellman_ford(const int start_v);
    std::vector<Edge> prim(const int start_v);

private:
    std::vector<std::list<Node>> a_list_;
	void sort_labels();

    int find_highest_index(const std::vector<Edge>& file_input) const;
    void fill_with_data(std::vector<std::list<Node>>& list, const std::vector<Edge>& file_input);

    void dijkstra(pair_pqueue& pq, pair_vector& cost_prev);
    bool pre_dijkstra_checks();
    bool negative_weights();
    std::vector<int> get_neighbours(const int vertex) const;
    void init_costs(pair_vector& cost_prev, const int start_v);
    bool update_cost(pair_vector& cost_prev, const int source, const int neighbour);
    int get_travel_cost(const int start_v, const int neighbour) const;

    pair_vector bellman_ford(std::deque<int>& vertex_q, pair_vector& cost_prev);
	void bf_relaxation(std::deque<int>& vertex_q, pair_vector& cost_prev);
	void slf_push(std::deque<int> &vertex_q, const int neighbour);

	void remove_loops();
    void prim(std::vector<Edge>& tree, std::vector<bool>& visited);
	bool all_visited(std::vector<bool>& visited);
	void add_to_queue(const unsigned index, edge_p_queue& edge_heap, const std::vector<bool>& visited);
    void add_reverse_edges(std::vector<Edge>& tree);
};