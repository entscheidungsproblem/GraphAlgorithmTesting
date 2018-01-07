#include "pape.hpp"
#include <deque>
#include <set>

vector<std::pair<float, optional<unsigned long>>> Pape::shortest_path(GraphADT* G, unsigned long start){
	float infin = std::numeric_limits<float>::infinity();
	unsigned long size = G->get_vertex_size();
	vector<std::pair<float, optional<unsigned long>>> vertices;
	
	std::pair<float,optional<unsigned long>> s (0,optional<unsigned long>{});
	vertices.push_back(s);
	
	for (unsigned long i = 1ul; i != size; i++){
		std::pair<float,optional<unsigned long>> p (infin,optional<unsigned long>{});
		vertices.push_back(p);
	}

	std::deque<unsigned long> Q;
	std::set<unsigned long> uniqueQ;
	std::set<unsigned long> visited;
	Q.push_back(0ul);
	uniqueQ.insert(0ul);
	visited.insert(0ul);

	while (!Q.empty()){
		unsigned long current = Q.front();
		Q.pop_front();
		uniqueQ.erase(current);
		// BOOST_ASSERT(size == vertices.size());
		for (unsigned long next = 0ul; next != size; next++){		
			if (G->check_edge(current*size + next) && G->get_edge(current*size + next) + std::get<0>(vertices[current]) < std::get<0>(vertices[next])){
				std::get<0>(vertices[next]) = G->get_edge(current*size + next) + std::get<0>(vertices[current]);
				std::get<1>(vertices[next]) = current;
				if (uniqueQ.find(next) == uniqueQ.end()){
					if (visited.find(next) == visited.end()){
						Q.push_back(next);
					}
					else{
						Q.push_front(next);
					}
					uniqueQ.insert(next);
					visited.insert(next);
				}
			}
		}
	}
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
