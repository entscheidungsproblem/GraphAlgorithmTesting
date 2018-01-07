#include "Dijkstra.hpp"

#include <queue>

#include <set>
#include <queue>
#include <vector>

using std::priority_queue;

vector<std::pair<float, optional<unsigned long>>>
	Dijkstra::shortest_path(GraphADT* G, unsigned long start){

	// Custom comparions for priority queue
	class compare{public: bool operator ()(std::pair<unsigned long, float>&p1, 
		std::pair<unsigned long, float>&p2){return p1.second>p2.second;}};
	
	// Set up queue and visited vector
	priority_queue<std::pair<unsigned long, float>,
		vector<std::pair<unsigned long, float>>, compare> Q;
	vector<bool> visited;
	
	unsigned long size = G->get_vertex_size();
	float infin = std::numeric_limits<float>::infinity();

	//Set up output
	vector<std::pair<float, optional<unsigned long>>> output;
	for (unsigned i = 0ul; i != size; i++){
		std::pair<float, optional<unsigned long>> p (infin,optional<unsigned long>{});
		output.push_back(p);
		visited.push_back(false);
	}

	// Set start values
	output[start].first = 0;
	Q.push(std::make_pair(start, 0.0));
	
	// While the queue is not empty
	while (!Q.empty()){
		// Dequeue the item
		std::pair<unsigned long, float> current = Q.top();
		Q.pop();

		// Get the cost and parent
		unsigned long index = current.first;
		float cost = current.second;

		// Skip if visited before
		if (visited[index]){
			continue;
		}
		visited[index] = true;
				
		// For add adjacent vertices
		for (unsigned long i = 0ul; i != size; i++){
			if (index != i && G->check_edge(index * size + i)){	//&& std::get<1>(output[i]).is_initialized()

				// If the path to i is reduced by taking current
				if(!visited[i] && G->get_edge(index * size + i) + cost < output[i].first){
					// Update output
					output[i].first = G->get_edge(index * size + i) + cost;
					output[i].second = index;
					Q.push(std::make_pair(i, output[i].first));
				}
			}
		}
	}

	return  output;
}
