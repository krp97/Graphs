#pragma once

class Node{

public:

Node() = delete;
Node(int end_node, int weight);

bool operator==(const Node& rhs) const;
bool operator!=(const Node& rhs) const;

int get_end_node() const;
int get_weight() const;

private:
    int end_node_;
    int weight_;
};