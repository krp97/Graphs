#include "../include/Adjacency_List.hpp"
#include <algorithm>

Adjacency_List::Adjacency_List(std::vector< std::list<int> > list)
    : a_list_{ list }
{}

Adjacency_List::Adjacency_List(const int size)
    : a_list_{ std::vector<std::list<int>> (size) }
{}

bool Adjacency_List::operator==(const Adjacency_List& rhs)
{
    auto vec_it{ a_list_.begin() };
    auto rhs_it{ rhs.a_list_.begin() };
    
    for(; vec_it != a_list_.end(); ++vec_it, ++rhs_it)
    {
       if(!std::equal((*vec_it).begin(), (*vec_it).end(), (*rhs_it).begin()))
            return false;
    }
    return true;
}

std::list<int>& Adjacency_List::operator[](const int index)
{
    return a_list_.at(index);
}

