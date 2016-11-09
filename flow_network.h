#ifndef FLOW_NETWORK
#define FLOW_NETWORK

#include <vector>
#include <algorithm>

struct Edge {
	bool existing_;
	int capacity_;
	int flow_;
};

class FlowNetwork {
	int vertices_quentity_;
	int edges_quentity_;
	int source_number_;
	int target_number_;
	std::vector<std::vector<Edge>> edges_;
	std::vector<int> excess_flow_;
	std::vector<int> height_;
public:
	FlowNetwork(int vertices_quentity, int edges_quentity, int source_number, int target_number);
	void AddEdge(int from, int to, int capacity);
	void Push(int from, int to); // push of flow
	void Relabel(int vertex); 
};


#endif
