#include "SPFA.hpp"
#include <limits>
#include <deque>
#include <set>
#include <boost/assert.hpp>

boost::container::vector<std::pair<float, boost::optional<unsigned long>>> SPFA::shortest_path(GraphADT* G, unsigned long start){
	// Initialize starting setup. Cost from source is infinity for all but the source. No parents are found to start.
	float infin = std::numeric_limits<float>::infinity();
	unsigned long size = G->get_vertex_size();
	boost::container::vector<std::pair<float, boost::optional<unsigned long>>> vertices;
	std::pair<float,boost::optional<unsigned long>> s (0,boost::optional<unsigned long>{});
	vertices.push_back(s);
	for (unsigned long i = 1ul; i != size; i++){
		std::pair<float,boost::optional<unsigned long>> p (infin,boost::optional<unsigned long>{});
		vertices.push_back(p);
	}

	// Setup the unique queue of vertices to relax. A set is used to guarantee that it is unique
	std::deque<unsigned long> Q;
	std::set<unsigned long> uniqueQ;
	Q.push_back(0ul);
	uniqueQ.insert(0ul);

	// While there is still vertices in the queue
	while (!Q.empty()){
		// dequeue
		unsigned long current = Q.front();
		Q.pop_front();
		uniqueQ.erase(current);
		BOOST_ASSERT(size == vertices.size());

		// For each neighbour, next, check if its cost can be reduced by setting current as the parent
		for (unsigned long next = 0ul; next != size; next++){		
			if (G->check_edge(current*size + next)){
				float potential_cost = G->get_edge(current*size + next) + std::get<0>(vertices[current]);
				if (potential_cost < std::get<0>(vertices[next])){
					std::get<0>(vertices[next]) = potential_cost;
					std::get<1>(vertices[next]) = current;
					// Only add to queue if next is not already in it
					if (uniqueQ.find(next) == uniqueQ.end()){
						Q.push_back(next);
						uniqueQ.insert(next);
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