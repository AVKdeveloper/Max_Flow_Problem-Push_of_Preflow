#include "flow_network.h"

FlowNetwork::FlowNetwork(int vertices_quentity, int edges_quentity, int source_number, int target_number) {
	vertices_quentity_ = vertices_quentity;
	edges_quentity_ = edges_quentity;
	source_number_ = source_number;
	target_number_ = target_number;
	edges_.resize(vertices_quentity_);
	height_.resize(vertices_quentity_);
	excess_flow_.resize(vertices_quentity_);
	for (int i = 0; i < vertices_quentity_; ++i) {
		edges_[i].resize(vertices_quentity_);
		for (int j = 0; j < vertices_quentity_; ++j) {
			edges_[i][j].existing_ = false;
			edges_[i][j].capacity_ = 0;
		}
	}
}

void FlowNetwork::AddEdge(int from, int to, int capacity) {
	if (!edges_[from][to].existing_) {
		edges_[from][to].existing_ = true;
		edges_[from][to].capacity_ = capacity;
		edges_[from][to].flow_ = 0;
		edges_[to][from].existing_ = true;
		edges_[to][from].capacity_ = capacity;
		edges_[to][from].flow_ = 0;
	} else { //if this edge already exists we can only increase the capacity
		edges_[from][to].capacity_ += capacity;
		edges_[to][from].capacity_ += capacity;
	}
}

void FlowNetwork::Push(int from, int to) {
	if (excess_flow_[from] > 0 && edges_[from][to].existing_ && height_[from] == height_[to] + 1) {
		int delta_of_pushing = std::min(excess_flow_[from], edges_[from][to].capacity_ - edges_[from][to].flow_);
		excess_flow_[from] -= delta_of_pushing;
		excess_flow_[to] += delta_of_pushing;
		edges_[from][to].flow_ += delta_of_pushing;
		edges_[to][from].flow_ -= delta_of_pushing;
	}
} 

void FlowNetwork::Relabel(int vertex) {
	if (excess_flow_[vertex] > 0) {
		int min_neihbour_height = height_[vertex];
		for (int i = 0; i < vertices_quentity_; ++i) {
			if (edges_[vertex][i].existing_ && min_neihbour_height > height_[i]) {
				min_neihbour_height = height_[i];
				break;
			}
		}
		if (height_[vertex] >= min_neihbour_height) {
			height_[vertex] = min_neihbour_height + 1;
		}
	}
}

void FlowNetwork::InitializePreflow() {
	for (int i = 0; i < vertices_quentity_; ++i) {
		height_[i] = 0;
		excess_flow_[i] = 0;
		for (int j = 0; j < vertices_quentity_; ++j) {
			edges_[i][j].flow_ = 0;
		}
	}
	height_[source_number_] = edges_quentity_;
	for (int i = 0; i < edges_quentity_; ++i) {
		if (edges_[source_number_][i].existing_) {
			edges_[source_number_][i].flow_ = edges_[source_number_][i].capacity_;
			edges_[i][source_number_].flow_ = - edges_[source_number_][i].capacity_;
			excess_flow_[i] = edges_[source_number_][i].capacity_;
			excess_flow_[source_number_] -= edges_[source_number_][i].capacity_;
		}
	}
}