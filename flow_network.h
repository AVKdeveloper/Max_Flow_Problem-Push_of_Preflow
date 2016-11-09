#ifndef FLOW_NETWORK
#define FLOW_NETWORK

#include <vector>

struct Edge {
	int from_;
	int to_;
	int capacity_;
	int flow_;
};

class FlowNetwork {
	int vertices_quentity_;
	int edges_quentity_;
	std::vector<std::vector<std::pair<bool, Edge>>> edges_; // first is if we have an edge; second is an edge
public:
	FlowNetwork(int vertices_quentity, int edges_quentity);
};


#endif
