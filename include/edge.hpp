#pragma once

class Edge{

public:

    Edge() = delete;
    Edge(int start, int end, int weight);

    int get_start() const;
    int get_end() const;
    int get_weight() const;

    bool operator==(const Edge& rhs) const;
    bool operator!=(const Edge& rhs) const;

	// Used by priority queues in algorithms.
	struct compare {
		
		bool operator()(const Edge& lhs, const Edge& rhs) const
		{
			return lhs.weight_ > rhs.weight_;
		}
	};

private:
    int start_;
    int end_;
    int weight_;

};