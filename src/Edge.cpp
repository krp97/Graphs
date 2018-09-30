#include "../include/Edge.hpp"

Edge::Edge(int start, int end, int weight)
    : start_{ start }, end_{ end }, weight_{ weight }
{}

bool Edge::operator==(const Edge& rhs) const
{
    bool start{ (start_ == rhs.start_) };
    bool end{ (end_ == rhs.end_) };
    bool weight{ (weight_ == rhs.weight_) };
    
    if(start && end && weight)
        return true;
    else 
        return false;
}

bool Edge::operator!=(const Edge& rhs) const
{
    return !(*this == rhs);
}

bool Edge::operator<(const Edge& rhs) const
{
    if(weight_ < rhs.weight_)
        return true;
    else
        return false;
}

bool Edge::operator>(const Edge& rhs) const
{
    return !((*this) < rhs);
}

int Edge::get_start() const
{
    return start_;
}

int Edge::get_end() const
{
    return end_;
}

int Edge::get_weight() const
{
    return weight_;
}