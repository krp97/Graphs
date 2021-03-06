#include "../include/adjacency_list.hpp"

#include <algorithm>
#include <climits>
#include <math.h>
#include <iostream>

Adjacency_List::Adjacency_List(std::vector<std::list<Node>> list)
    : a_list_{ list }
{
	sort_labels();
}

Adjacency_List::Adjacency_List(std::vector<Edge> file_input)
{
	int size{ find_highest_index(file_input) + 1 };
    auto input{ std::vector<std::list<Node>>(size, std::list<Node>()) };
    fill_with_data(input, file_input);
    a_list_ = input;
	sort_labels();
}

void Adjacency_List::sort_labels()
{
	for (auto& l : a_list_)
		l.sort(Node::label_comp());
}

bool Adjacency_List::operator==(const Adjacency_List& rhs) const
{
	if (a_list_ == rhs.a_list_)
		return true;
	return false;
}

bool Adjacency_List::operator!=(const Adjacency_List& rhs) const
{
    return !(*this == rhs);
}

const std::list<Node>& Adjacency_List::operator[](const int index) const
{
    return a_list_.at(index);
}

std::string Adjacency_List::to_string() const
{
	auto out{ std::string() };
	int index{ 0 };
	for (auto& list : a_list_)
	{
		out += std::to_string(index);
		std::for_each(list.begin(), list.end(), [&out](const Node& n) {
			out += n.to_string() + ','; 
		});
		out += "\n";
		++index;
	}
	return out;
}

int Adjacency_List::find_highest_index(const std::vector<Edge>& file_input) const
{
    int index{0};
    for(auto& edge : file_input)
    {
        if(index < edge.get_start())
            index = edge.get_start();
    }
    return index;
}
void Adjacency_List::fill_with_data(std::vector<std::list<Node>>& list, const std::vector<Edge>& file_input)
{
    int start, end, weight;
    for(auto& edge: file_input)
    {
        start = edge.get_start();
        end = edge.get_end();
        weight = edge.get_weight();
        list.at(start).push_back(Node(end, weight));
    }
}

Adjacency_List::pair_vector Adjacency_List::dijkstra(const int start_v)
{
    if(pre_dijkstra_checks())
    {
        auto pq{ pair_pqueue() };
        pq.push(std::pair<int,int>(0, start_v));

        auto cost_prev{ pair_vector() };
        init_costs(cost_prev, start_v);
        while(!pq.empty())
            dijkstra(pq, cost_prev);

        return cost_prev;
    }
    return pair_vector();
}

bool Adjacency_List::pre_dijkstra_checks()
{
    if(a_list_.size() == 0)
        return false;
    if(negative_weights())
        return false;
        
    return true;
}

bool Adjacency_List::negative_weights()
{
    for(auto& lists: a_list_)
    {
        for(auto& nodes: lists)
        {
            if(nodes.get_weight() < 0)
                return true;
        }
    }
    return false;
}

void Adjacency_List::init_costs(pair_vector& cost_prev, const int start_v)
{
    for(unsigned int i{0}; i < a_list_.size(); ++i)
        cost_prev.push_back(std::pair<int,int>(INT_MAX, INT_MAX));

    cost_prev.at(start_v).first = 0;
    cost_prev.at(start_v).second = start_v;
}

void Adjacency_List::dijkstra(pair_pqueue& pq, pair_vector& cost_prev)
{
	int v_index{ pq.top().second };
    pq.pop();

    auto neighbours{ get_neighbours(v_index) };

    int updated_weight;
    for(auto& n_it: neighbours)
    {
        bool cost_updated{ update_cost(cost_prev, v_index, n_it) };
        if(cost_updated)
        {
            updated_weight = cost_prev.at(n_it).first;
            pq.push(std::pair<int,int>(updated_weight, n_it));
        }             
    }
}

std::vector<int> Adjacency_List::get_neighbours(const int node) const
{
    auto neighbours{ std::vector<int>() };

    int index;
	for (auto& list_it : a_list_.at(node))
    {
        index = list_it.get_end_node();
        neighbours.push_back(index);
    }
    return neighbours;
}

bool Adjacency_List::update_cost(pair_vector& cost_prev, const int source, const int neighbour)
{
    const int base_cost{ cost_prev.at(source).first };
    const int travel_cost{ get_travel_cost(source, neighbour) };
    const int updated_cost{ base_cost + travel_cost };
    const int current_cost{ cost_prev.at(neighbour).first };

    if(updated_cost < current_cost)
    {
        cost_prev.at(neighbour) = std::pair<int,int>(updated_cost, source);
        return true;
    }
    return false;
}

int Adjacency_List::get_travel_cost(const int start_v, const int neighbour) const
{
	for (auto& list_it : a_list_.at(start_v))
	{
		if (list_it.get_end_node() == neighbour)
			return list_it.get_weight();
	}
    return -1;
}

std::vector<std::pair<int, int>> Adjacency_List::bellman_ford(const int start_v)
{
	if (a_list_.size() > 0)
	{
		std::deque<int> vertex_q{ std::deque<int>() };
		vertex_q.push_front(start_v);

		pair_vector cost_prev{ pair_vector() };
		init_costs(cost_prev, start_v);
        
		return bellman_ford(vertex_q, cost_prev);
	}
	else
		return pair_vector();
}

Adjacency_List::pair_vector Adjacency_List::bellman_ford(std::deque<int>& vertex_q, Adjacency_List::pair_vector& cost_prev)
{
    // Each node is pushed to the queue at most V - 1 times.
    size_t nodes{ a_list_.size() };
    size_t iterations{ nodes - 1};
    size_t negative_cycle{nodes * iterations};

	while (!vertex_q.empty())
	{
        if(negative_cycle == 0)
            return pair_vector();
        negative_cycle--;
		bf_relaxation(vertex_q, cost_prev);
	}
	return cost_prev;
}

void Adjacency_List::bf_relaxation(std::deque<int>& vertex_q, Adjacency_List::pair_vector& cost_prev)
{
	int vertex{ vertex_q.front() };
	vertex_q.pop_front();
	
	std::vector<int> neighbours{ get_neighbours(vertex) };

	bool updated_f{false};
	for(auto& neighbour : neighbours)
	{
		updated_f = update_cost(cost_prev, vertex, neighbour);
		if (updated_f)
			slf_push(vertex_q, neighbour);
	}
}

void Adjacency_List::slf_push(std::deque<int>& vertex_q, const int vertex)
{
    auto find_v{ std::find(vertex_q.begin(), vertex_q.end(), vertex) };
    bool exists{ find_v != vertex_q.end() };

	if(vertex_q.empty())
		vertex_q.push_back(vertex);
	else if (vertex < vertex_q.front() && !exists)
		vertex_q.push_front(vertex);
	else if (!exists)
		vertex_q.push_back(vertex);
}

std::vector<Edge> Adjacency_List::prim(const int start_v)
{
	if (a_list_.size() > 0)
	{
		auto tree{ std::vector<Edge>() };
		auto visited{ std::vector<bool>(a_list_.size(), false) };
		visited.at(start_v) = true;

		auto list_copy{ Adjacency_List(*this) };
		list_copy.remove_loops();
		list_copy.prim(tree, visited);
		add_reverse_edges(tree);

		return tree;
	}
	else
		return std::vector<Edge>();
}

void Adjacency_List::remove_loops()
{
	int index{ 0 };
	for (auto& lists : a_list_)
	{
		lists.remove_if([&index](Node& n){
			return (index == n.get_end_node());
		});
		++index;
	}
}

void Adjacency_List::prim(std::vector<Edge>& tree, std::vector<bool>& visited)
{
	auto edge_q{ edge_p_queue() };
	int prev_visited{ 0 };

	while (!all_visited(visited))
	{
		add_to_queue(prev_visited, edge_q, visited);

		auto mst_e{ edge_q.top() };
		tree.push_back(mst_e);
		visited.at(mst_e.get_end()) = true;
		prev_visited = mst_e.get_end();

		edge_q.pop();
	}
}

bool Adjacency_List::all_visited(std::vector<bool>& visited)
{
	for(auto& node: visited)
		if(node == false)
			return false;
	return true;
}

void Adjacency_List::add_to_queue(const unsigned index, Adjacency_List::edge_p_queue& edge_q, const std::vector<bool>& visited)
{
	int weight{ 0 };
	for (auto& n_it: a_list_.at(index))
	{
		if (!visited.at(n_it.get_end_node()))
		{
			weight = n_it.get_weight();
			edge_q.push(Edge(index, n_it.get_end_node(), weight));
		}
	}
}

void Adjacency_List::add_reverse_edges(std::vector<Edge>& tree)
{
	std::vector<Edge> temp_tree{ tree };
	for (auto& e : temp_tree)
		tree.push_back(Edge(e.get_end(), e.get_start(), e.get_weight()));
}