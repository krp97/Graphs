#include "../include/node.hpp"

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

bool Node::operator<(const Node& rhs) const
{
    return end_node_ < rhs.end_node_ ? true : false;
}

bool Node::operator>(const Node& rhs) const
{
    return end_node_ > rhs.end_node_ ? true : false;
}

int Node::get_end_node() const
{
    return end_node_;
}

int Node::get_weight() const
{
    return weight_;
}

std::string Node::to_string() const
{
	return std::string('(' + std::to_string(end_node_) +
	 ',' + std::to_string(weight_) + ')');
}