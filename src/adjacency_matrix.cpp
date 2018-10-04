#include <climits>
#include <iostream>

#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>> matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const std::vector<Edge>& data)
{
    int size{ find_highest_vertex(data) + 1 };
    auto input{ std::vector<std::vector<int>>(size, std::vector<int>(size)) };
    fill_w_data(input, data);
    a_matrix_ = input;
}

const std::vector<int>& Adjacency_Matrix::operator[](const int index) const
{
    return a_matrix_.at(index);
}

bool Adjacency_Matrix::operator==(const Adjacency_Matrix& rhs) const
{
	if (a_matrix_ == rhs.a_matrix_)
		return true;
	return false;
}

bool Adjacency_Matrix::operator!=(const Adjacency_Matrix& rhs) const
{
    return !(*this==rhs);
}

int Adjacency_Matrix::get_size() const
{
    return a_matrix_.size();
}

int Adjacency_Matrix::find_highest_vertex(const std::vector<Edge>& data) const
{
    int index{0};
    for(auto& edge: data)
    {
        if(edge.get_start() > index)
            index = edge.get_start();
        if(edge.get_end() > index)
            index = edge.get_end();
    }
    return index;
}

void Adjacency_Matrix::fill_w_data(std::vector<std::vector<int>>& empty_mat, const std::vector<Edge>& data)
{
    int start, end, weight;
    for(auto& edge: data)
    {
        start = edge.get_start();
        end = edge.get_end();
        weight = edge.get_weight();

        empty_mat.at(start).at(end) = weight;
    }
}

// Within the dijkstra's algorithm std::pair<int,int>::first is used as
// a cost of travel to std::pair<int,int>::second.
std::vector<std::pair<int, int>> Adjacency_Matrix::dijkstra(const int start_v)
{
    if(pre_dijkstra_checks())
    {
        auto cost_prev{ pair_vector(a_matrix_.size()) };
        init_costs(cost_prev, start_v);

		dijkstra(cost_prev, start_v);
        return cost_prev;
    }
    return pair_vector();
}

bool Adjacency_Matrix::pre_dijkstra_checks()
{
    if(a_matrix_.size() <= 0)
        return false;
    if(!negative_weights())
        return false;
    
    return true;
}

bool Adjacency_Matrix::negative_weights()
{
    for(auto& rows: a_matrix_)
    {
        for(auto& cols: rows)
        {
            if(cols < 0)
                return false;
        }
    }
    return true;    
}

void Adjacency_Matrix::init_costs(pair_vector& cost_prev, const int start_v)
{
	for(auto& p : cost_prev)
		p = std::pair<int, int>(INT_MAX, INT_MAX);

    cost_prev.at(start_v).first = 0;
    cost_prev.at(start_v).second = start_v;
}

void Adjacency_Matrix::dijkstra(pair_vector& cost_prev, const int start_v)
{
	auto pq{ pair_p_queue() };
	pq.push(std::pair<int, int>(0, start_v));

	while (!pq.empty())
		dijkstra_relaxation(pq, cost_prev);
}

void Adjacency_Matrix::dijkstra_relaxation(pair_p_queue & pq, pair_vector & cost_prev)
{
	int v_index{ pq.top().second };
	pq.pop();

	auto neighbours{ get_neighbours(v_index) };

	int updated_weight;
	for (auto& n_it : neighbours)
	{
		bool cost_updated{ update_cost(cost_prev, v_index, n_it) };
		if (cost_updated)
		{
			updated_weight = cost_prev.at(n_it).first;
			pq.push(std::pair<int, int>(updated_weight, n_it));
		}
	}
}

std::vector<int> Adjacency_Matrix::get_neighbours(const int node) const
{
    auto out_neighbours{ std::vector<int>() };

	int index, counter{0};
	for (auto& mat_it : a_matrix_.at(node))
	{
		if (mat_it != 0)
		{
			index = counter;
			out_neighbours.push_back(index);
		}
		++counter;
	}
    return out_neighbours;
}

bool Adjacency_Matrix::update_cost(pair_vector& cost_prev, const int source, const int neighbour)
{
    int base_cost{ cost_prev.at(source).first };
    int travel_cost{ a_matrix_.at(source).at(neighbour) };
    int updated_cost{ base_cost + travel_cost };
    int current_cost{ cost_prev.at(neighbour).first };

    if(updated_cost < current_cost)
    {
        cost_prev.at(neighbour) = std::pair<int,int>(updated_cost, source);
        return true;
    }
    return false;
}

Adjacency_Matrix::pair_vector Adjacency_Matrix::bellman_ford(const int start_v)
{
	if (a_matrix_.size() > 0)
	{
		std::deque<int> vertex_q{ std::deque<int>() };
		vertex_q.push_front(start_v);

		pair_vector cost_prev{ pair_vector(a_matrix_.size()) };
		init_costs(cost_prev, start_v);
		bellman_ford(vertex_q, cost_prev);

		return cost_prev;
	}
	else
		return pair_vector();
}

void Adjacency_Matrix::bellman_ford(std::deque<int>& vertex_q, Adjacency_Matrix::pair_vector& cost_prev)
{
    // Each node is pushed to the queue at most V - 1 times.
    size_t nodes{ a_matrix_.size() };
    size_t iterations{ nodes - 1};
    size_t negative_cycle{nodes * iterations};

	while (!vertex_q.empty())
	{
		if (negative_cycle == 0)
		{
			cost_prev = pair_vector();
			break;
		}
        negative_cycle--;
		bf_relaxation(vertex_q, cost_prev);
	}
}

void Adjacency_Matrix::bf_relaxation(std::deque<int>& vertex_q, Adjacency_Matrix::pair_vector& cost_prev)
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

void Adjacency_Matrix::slf_push(std::deque<int>& vertex_q, const int vertex)
{
    auto find_v{ std::find(vertex_q.begin(), vertex_q.end(), vertex) };
    bool exists{ find_v != vertex_q.end() };

	if (vertex_q.empty())
		vertex_q.push_back(vertex);
	else if (vertex < vertex_q.front() && !exists)
		vertex_q.push_front(vertex);
	else if (!exists)
		vertex_q.push_back(vertex);
}

std::vector<Edge> Adjacency_Matrix::prim(const int start_v)
{
	if (a_matrix_.size() > 0)
	{
		auto tree{ std::vector<Edge>() };
		auto visited{ std::vector<bool>(a_matrix_.size(), false) };
		visited.at(start_v) = true;
		prim(tree, visited);

		return tree;
	}
	else
		return std::vector<Edge>();
}

void Adjacency_Matrix::prim(std::vector<Edge>& tree, std::vector<bool>& visited)
{
	auto edge_q{ edge_p_queue() };

	for (size_t i{ a_matrix_.size() - 1 }; i > 0; --i)
	{
		update_edge_queue(edge_q, visited);
		auto mst_e{ edge_q.top() };
		tree.push_back(mst_e);
		visited.at(mst_e.get_end()) = true;
		
		edge_q.pop();
	}
}

void Adjacency_Matrix::update_edge_queue(Adjacency_Matrix::edge_p_queue& edge_q, const std::vector<bool>& visited)
{
	for (size_t i{ 0 }; i < visited.size(); ++i)
	{
		if (visited.at(i))
			add_to_queue(i, edge_q, visited);
	}
}

void Adjacency_Matrix::add_to_queue(const unsigned index, Adjacency_Matrix::edge_p_queue& edge_q, const std::vector<bool>& visited)
{
	auto neighbours{ get_neighbours(index) };

	int weight{ 0 };
	for (auto& n_it: neighbours)
	{
		if (!visited.at(n_it))
		{
			weight = a_matrix_.at(index).at(n_it);
			edge_q.push(Edge(index, n_it, weight));
		}
	}
}
