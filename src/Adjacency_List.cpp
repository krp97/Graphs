#include "../include/Adjacency_List.hpp"
#include <algorithm>
#include <climits>
#include <math.h>

Adjacency_List::Adjacency_List(std::vector<std::list<Node>> list)
    : a_list_{ list }
{}

Adjacency_List::Adjacency_List(std::vector<Edge> file_input)
{
    int size = find_highest_index(file_input) + 1;
    auto input{ std::vector<std::list<Node>>(size, std::list<Node>()) };
    fill_with_data(input, file_input);
    a_list_ = input;
}

bool Adjacency_List::operator==(const Adjacency_List& rhs) const
{
	if (a_list_.size() == rhs.a_list_.size())
	{
		auto rhs_it{ rhs.a_list_.begin() };
		for (auto& list : a_list_)
		{
			if (list != (*rhs_it))
				return false;
			++rhs_it;
		}
		return true;
	}
	else
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
    for(int i{0}; i<a_list_.size(); ++i)
        cost_prev.push_back(std::pair<int,int>(INT_MAX, INT_MAX));

    cost_prev.at(start_v).first = 0;
    cost_prev.at(start_v).second = start_v;
}

void Adjacency_List::dijkstra(pair_pqueue& pq, pair_vector& cost_prev)
{
    auto vertex{ pq.top() };
    pq.pop();

    int v_cost{ vertex.first }, v_index{ vertex.second };
    auto neighbours{ extract_neighbours(v_index) };

    int updated_weight;
    for(auto n_it{ neighbours.begin() }; n_it != neighbours.end(); ++n_it)
    {
        bool cost_updated{ update_cost(cost_prev, v_index, (*n_it)) };
        if(cost_updated)
        {
            updated_weight = cost_prev.at((*n_it)).first;
            pq.push(std::pair<int,int>(updated_weight, (*n_it)));
        }             
    }
}

std::vector<int> Adjacency_List::extract_neighbours(const int node)
{
    auto out_neighbours{ std::vector<int>() };

    auto list_it{ a_list_.at(node).begin() };
    auto it_end{ a_list_.at(node).end() };
    int index;
    for(; list_it != it_end; ++list_it)
    {
        index = (*list_it).get_end_node();
        out_neighbours.push_back(index);
    }
    return out_neighbours;
}

bool Adjacency_List::update_cost(pair_vector& cost_prev, const int source, const int neighbour)
{
    int base_cost{ cost_prev.at(source).first };
    int travel_cost{ get_travel_cost(source, neighbour) };
    int updated_cost{ base_cost + travel_cost };
    int current_cost{ cost_prev.at(neighbour).first };

    if(updated_cost < current_cost)
    {
        cost_prev.at(neighbour) = std::pair<int,int>(updated_cost, source);
        return true;
    }
    return false;
}

int Adjacency_List::get_travel_cost(const int start_v, const int neighbour) const
{
    auto list_it{ a_list_.at(start_v).begin() };
    auto list_end{ a_list_.at(start_v).end() };

    for(; list_it != list_end; ++list_it)
        if((*list_it).get_end_node() == neighbour)
            return (*list_it).get_weight();

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
	
	std::vector<int> neighbours{ extract_neighbours(vertex) };

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

	if (vertex < vertex_q.front() && !exists)
		vertex_q.push_front(vertex);
	else if(!exists)
		vertex_q.push_back(vertex);
}