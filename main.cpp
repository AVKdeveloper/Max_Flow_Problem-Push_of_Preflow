// This program finds max flow in undirected graph
//
//

#include <iostream>
#include "flow_network.h"

int main() {
	while (true) {
		int vertices_quantity;// quantity of vertices in graph
		std::cin >> vertices_quantity;
		if (vertices_quantity == 0) {
			break;
		}
		int source_number;// number of source
		int target_number;// number of target
		int edges_quantity;// quantity of edges in graph
		std::cin >> source_number >> target_number >> edges_quantity;

		FlowNetwork net(vertices_quantity, edges_quantity, source_number, target_number);
		int from_number;// number of vertex, which is begin of edge
		int to_number; // number of vertex, which is end of edge
		int capacity; // capacity of flow throught this edge
		for (int i = 0; i < edges_quantity; ++i) {
			std::cin >> from_number >> to_number >> capacity;
			net.AddEdge(from_number, to_number, capacity);
		}

	}
	

	return 0;
}