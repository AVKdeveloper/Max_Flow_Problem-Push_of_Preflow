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
	FlowNetwork(const int& vertices_quentity, const int& edges_quentity, const int& source_number, const int& target_number);
	void AddEdge(const int& from, const int& to, const int& capacity);
	bool Push(const int& from, const int& to); // push of flow
	bool Relabel(const int& vertex);
	void InitializePreflow();
	void PushRelabelOfPreflow();
	int FindMaxFlow();
};


#endif
