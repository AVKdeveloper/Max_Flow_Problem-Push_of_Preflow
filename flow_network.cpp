#include "flow_network.h"

FlowNetwork::FlowNetwork(const int& vertices_quentity, const int& edges_quentity, 
	                     const int& source_number, const int& target_number) {
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

void FlowNetwork::AddEdge(const int& from, const int& to, const int& capacity) {
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

bool FlowNetwork::Push(const int& from, const int& to) {
	if (excess_flow_[from] > 0 && edges_[from][to].existing_ && height_[from] == height_[to] + 1) {
		int delta_of_pushing = std::min(excess_flow_[from], edges_[from][to].capacity_ - edges_[from][to].flow_);
		excess_flow_[from] -= delta_of_pushing;
		excess_flow_[to] += delta_of_pushing;
		edges_[from][to].flow_ += delta_of_pushing;
		edges_[to][from].flow_ -= delta_of_pushing;
		return true;
	} else {
		return false;
	}
} 

bool FlowNetwork::Relabel(const int& vertex) {
	if (vertex != source_number_ && vertex != target_number_ && excess_flow_[vertex] > 0) {
		int min_neihbour_height = 2 * height_[vertex];// there are theorem that for every vertex height[vertex] < 2V-2
		for (int i = 0; i < vertices_quentity_; ++i) {
			if (edges_[vertex][i].existing_ && min_neihbour_height > height_[i]) {
				min_neihbour_height = height_[i];
			}
		}
		if (height_[vertex] <= min_neihbour_height) {
			height_[vertex] = min_neihbour_height + 1;
			return true;
		} else {
			return false;
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

void FlowNetwork::PushRelabelOfPreflow() {
	InitializePreflow();
	bool done_operations = true;// indicator that we have done at least one operation
	while (done_operations) { // estimation: ~E times
		done_operations = false;
		for (int i = 0; i < vertices_quentity_; ++i) {// O(V)
			if (excess_flow_[i] > 0) {
				done_operations |= Relabel(i); // O(V)
				for (int j = 0; j < vertices_quentity_; ++j) { // O(V)
					done_operations |= Push(i, j);
				}
			}
		}
	}
}

int FlowNetwork::FindMaxFlow() {
	PushRelabelOfPreflow();
	if (excess_flow_[source_number_] == excess_flow_[target_number_]) {
		return excess_flow_[target_number_];
	} else {
		return -1;
	}
}