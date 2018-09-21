#include "../include/Node.hpp"

Node::Node(int end_node, int weight)
    : end_node_{ end_node }, weight_{ weight }
{}

bool Node::operator==(const Node& rhs) const
{
    bool dest_check{ (end_node_ == rhs.end_node_) };
    bool weight_check{ (weight_ == rhs.weight_) };

    if(dest_check && weight_check)
        return true;
    else
        return false;
}

bool Node::operator!=(const Node& rhs) const
{
    return !(*this == rhs);
}

int Node::get_end_node() const
{
    return end_node_;
}

int Node::get_weight() const
{
    return weight_;
}