#pragma once
#include <string>

class Node{

public:

	Node() = delete;
	Node(int end_node, int weight);
	
	bool operator==(const Node& rhs) const;
	bool operator!=(const Node& rhs) const;
	bool operator<(const Node& rhs) const;
	bool operator>(const Node& rhs) const;
	
	int get_end_node() const;
	int get_weight() const;
	
	std::string to_string() const;

	struct label_comp {

		bool operator()(const Node& lhs, const Node& rhs) const
		{
			return lhs.end_node_ > rhs.end_node_;
		}
	};

private:
    int end_node_;
    int weight_;
};