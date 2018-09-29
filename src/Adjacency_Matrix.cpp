#include <climits>
#include <iostream>

#include "../include/Adjacency_Matrix.hpp"
#include "../include/File_Handler.hpp"

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
	if (a_matrix_.size() != rhs.a_matrix_.size())
		return false;

	auto rhs_it{ rhs.a_matrix_.begin() };
	for(auto& mat_it : a_matrix_)
	{
	    if(mat_it != (*rhs_it))
	        return false;
	    ++rhs_it;
	}
	return true;    
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
        auto pq{ pair_p_queue() };
        pq.push(std::pair<int,int>(0, start_v));

        auto cost_prev{ pair_vector() };
        init_costs(cost_prev, start_v);
        while(!pq.empty())
            dijkstra(pq, cost_prev);

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
    for(auto& rows : a_matrix_)
        cost_prev.push_back(std::pair<int,int>(INT_MAX, INT_MAX));

    cost_prev.at(start_v).first = 0;
    cost_prev.at(start_v).second = start_v;
}

void Adjacency_Matrix::dijkstra(pair_p_queue& pq, pair_vector& cost_prev)
{
    int v_index{ pq.top().second };
	pq.pop();

    auto neighbours{ extract_neighbours(v_index) };

    int updated_weight;
    for(auto& n_it : neighbours)
    {
        bool cost_updated{ update_cost(cost_prev, v_index, n_it) };
        if(cost_updated)
        {
            updated_weight = cost_prev.at(n_it).first;
            pq.push(std::pair<int,int>(updated_weight, n_it));
        }             
    }
}

std::vector<int> Adjacency_Matrix::extract_neighbours(const int node)
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

		pair_vector cost_prev{ pair_vector() };
		init_costs(cost_prev, start_v);
        
		return bellman_ford(vertex_q, cost_prev);
	}
	else
		return pair_vector();
}

Adjacency_Matrix::pair_vector Adjacency_Matrix::bellman_ford(std::deque<int>& vertex_q, Adjacency_Matrix::pair_vector& cost_prev)
{
    // Each node is pushed to the queue at most V - 1 times.
    size_t nodes{ a_matrix_.size() };
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

void Adjacency_Matrix::bf_relaxation(std::deque<int>& vertex_q, Adjacency_Matrix::pair_vector& cost_prev)
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

void Adjacency_Matrix::slf_push(std::deque<int>& vertex_q, const int vertex)
{
    auto find_v{ std::find(vertex_q.begin(), vertex_q.end(), vertex) };
    bool exists{ find_v != vertex_q.end() };

	if (vertex < vertex_q.front() && !exists)
		vertex_q.push_front(vertex);
	else if(!exists)
		vertex_q.push_back(vertex);
}
