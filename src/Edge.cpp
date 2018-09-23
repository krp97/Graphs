#include "../include/Edge.hpp"

Edge::Edge(int start, int end, int weight)
    : start_{ start }, end_{ end }, weight_{ weight }
{}

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