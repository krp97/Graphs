#include "../include/Adjacency_List.hpp"
#include <algorithm>
#include <climits>

Adjacency_List::Adjacency_List(std::vector< std::list<Node> > list)
    : a_list_{ list }
{}

Adjacency_List::Adjacency_List(const int size)
    : a_list_{ std::vector<std::list<Node>> (size, std::list<Node>()) }
{}

bool Adjacency_List::operator==(const Adjacency_List& rhs) const
{
    auto vec_it{ a_list_.begin() };
    auto rhs_it{ rhs.a_list_.begin() };
    
    for(; vec_it != a_list_.end(); ++vec_it, ++rhs_it)
    {
       if((*vec_it) != (*rhs_it))
            return false;
    }
    return true;
}

bool Adjacency_List::operator!=(const Adjacency_List& rhs) const
{
    return !(*this == rhs);
}

const std::list<Node>& Adjacency_List::operator[](const int index) const
{
    return a_list_.at(index);
}

Adjacency_List::pair_vector Adjacency_List::dijkstra(const int start_v)
{
    auto pq{ pair_pqueue() };
    pq.push(std::pair<int,int>(0, start_v));

    auto cost_prev{ pair_vector() };
    init_costs(cost_prev, start_v);
    while(!pq.empty())
        dijkstra(pq, cost_prev);

    return cost_prev;
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
