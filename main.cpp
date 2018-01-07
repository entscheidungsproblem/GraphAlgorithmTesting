#include "DataStructures/graphADT.hpp"
#include "DataStructures/adjacency_matrix.hpp"
#include "DataStructures/graph_converter.hpp"
#include "RandomGraph/random_graph_generator.hpp"
#include "RandomGraph/graphBuilder.hpp"
#include "Algorithms/bellman_ford.hpp"
#include "Algorithms/SPFA.hpp"
#include "Algorithms/pape.hpp"
#include "Algorithms/Dijkstra.hpp"
#include "Algorithms/SSSP.hpp"
#include "timer.hpp"

#include <utility>      // std::pair, std::get
#include <string>
#include <set>
#include <vector>

using std::vector;
using std::set;
using std::string;

int main() { 

	// Create the builder and set the arguments
	Builder b;
	b.setAcyclic( true ).setDirected( true ).setSelfLoops( false ).setNumberVertices( 10 ).setNumberVertices( 20 ).setweight( 0, 10 );
	
	// Run the timer on the specified algorithms and number of test cases
	/*
	TimeSSSP* T = new TimeSSSP(&b);
	T->run<BellmanFord, SPFA, Pape, Dijkstra>(100);
	boost::container::vector<float> avg = T->average();
	// And print the results
	printf("size= %lu, averages:\n", avg.size());
	for (auto i = avg.begin(); i != avg.end(); i++){
		printf("%.2f, ", *i);
	}
	*/

	// or run the algorithms on individual graphs to get results which can produce graphviz dot files
	
	GraphADT* G = b.build();
	SSSP alg;
	alg.setup(G, 0ul);
	vector<set<unsigned long>> results = alg.run<BellmanFord, SPFA, Pape>(true);
	// And print the results
	vector<string> filenames = {"BellmanFord", "SPFA", "Pape"};
	for (uint i = 0; i != filenames.size(); i++){
		G->export_dot(filenames[i],results[i]);
	}

	
}
