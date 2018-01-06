#include "bellman_ford.hpp"
#include <limits>

boost::container::vector<std::pair<float, boost::optional<unsigned long>>> BellmanFord::shortest_path(GraphADT* G, unsigned long start){
	// Initialize starting setup. Cost from source is infinity for all but the source. No parents are found to start.
	float infin = std::numeric_limits<float>::infinity();
	unsigned long size = G->get_vertex_size();
	boost::container::vector<std::pair<float, boost::optional<unsigned long>>> vertices;
	for (unsigned long i = 0ul; i != size; i++){
		std::pair<float,boost::optional<unsigned long>> p (infin,boost::optional<unsigned long>{});
		vertices.push_back(p);
	}
	std::get<0>(vertices[start]) = 0;

	// First, iterate over the number of edges in the SP tree (size-1). 
	// During each iteration, relax all edges to reduce cost
	for (unsigned long i = 1ul; i != size; i++){
		for (unsigned long j = 0ul; j != size; j++){
			for (unsigned long k = 0ul; k != size; k++){
				if (G->check_edge(j*size + k)){
					if (G->get_edge(j*size + k) + std::get<0>(vertices[j]) < std::get<0>(vertices[k])){
						std::get<0>(vertices[k]) = G->get_edge(j*size + k) + std::get<0>(vertices[j]);
						std::get<1>(vertices[k]) = j;
					}
				}
			}
		}
	}

	// If progress is still made by iterating once more, a negative cycle must be present
	for (unsigned long j = 0ul; j != size; j++){
		for (unsigned long k = 0ul; k != size; k++){
			if (G->check_edge(j*size + k)){
				if (G->get_edge(j*size + k) + std::get<0>(vertices[j]) < std::get<0>(vertices[k])){
					printf("Negative cycle detected");
					return vertices;
				}
			}
		}
	}
	return vertices;
}