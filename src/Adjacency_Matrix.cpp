#include "../include/Adjacency_Matrix.hpp"
#include <climits>
#include <iostream>

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>> matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const int size)
    : a_matrix_{ std::vector<std::vector<int>>(size, std::vector<int>(size, 0)) }
{}

const std::vector<int>& Adjacency_Matrix::operator[](const int index) const
{
    return a_matrix_.at(index);
}

bool Adjacency_Matrix::operator==(const Adjacency_Matrix& rhs) const
{
    if(a_matrix_ == rhs.a_matrix_)
    {
        auto rhs_it{ rhs.a_matrix_.begin() };

        for(auto& mat_it : a_matrix_)
        {
            if(mat_it != (*rhs_it))
                return false;
            ++rhs_it;
        }
        return true;
    }
    else 
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

// Within the dijkstra's algorithm std::pair<int,int>::first is used as
// a cost of travel to std::pair<int,int>::second.
Adjacency_Matrix::pair_vector Adjacency_Matrix::dijkstra(const int start_v)
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

bool Adjacency_Matrix::pre_dijkstra_checks()
{
    if(a_matrix_.size() <= 0)
        return false;
    if(!negative_weights())
        return false;
    if(!lone_nodes())
        return false;
    if(!undirected())
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

// Checks if any column of the matrix is filled with 0.
bool Adjacency_Matrix::lone_nodes()
{
    bool col_zero_check = true;
    for(int col_it{0}; col_it < a_matrix_.size(); ++col_it)
    {
        for(int row_it{0}; row_it < a_matrix_.size(); ++row_it)
        {
            if(a_matrix_.at(row_it).at(col_it) != 0)
            {
                col_zero_check = false;
            }
        }
        col_zero_check = true;
    }
    return col_zero_check;
}

bool Adjacency_Matrix::undirected()
{
    for(int row_it{0}; row_it < a_matrix_.size(); ++row_it)
    {
        for(int col_it{ row_it + 1 }; col_it < a_matrix_.size(); ++col_it)
        {
            if(a_matrix_[row_it][col_it] != a_matrix_[col_it][row_it])
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

void Adjacency_Matrix::dijkstra(pair_pqueue& pq, pair_vector& cost_prev)
{
    auto vertex{ pq.top() };
    pq.pop();

    int v_cost{ vertex.first }, v_index{ vertex.second };
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
    int index;

    auto mat_it{ a_matrix_.at(node).begin() };
    auto it_end{ a_matrix_.at(node).end() };
    for(; mat_it != it_end; ++mat_it)
    {
        if((*mat_it) != 0)
        {
            index = mat_it - a_matrix_.at(node).begin();
            out_neighbours.push_back(index);
        }
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