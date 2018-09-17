#pragma once
#include <list>
#include <vector>

class Adjacency_List{

public:

    Adjacency_List(std::vector< std::list<int> > list);
    Adjacency_List(const int size);

    bool operator==(const Adjacency_List& rhs);
    std::list<int>& operator[](const int index);

private:
    std::vector< std::list<int> > a_list_;
};