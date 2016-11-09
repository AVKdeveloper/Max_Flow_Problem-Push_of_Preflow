#include "flow_network.h"

FlowNetwork::FlowNetwork(int vertices_quentity, int edges_quentity) {
	vertices_quentity_ = vertices_quentity;
	edges_quentity_ = edges_quentity;
	edges_.resize(vertices_quentity_);
	for (int i = 0; i < vertices_quentity_; ++i) {
		edges_[i].resize(vertices_quentity_);
		for (int j = 0; j < vertices_quentity_; ++j) {
			edges_[i][j].first = false;
		}
	}
}
