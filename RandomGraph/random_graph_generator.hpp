#ifndef RAND_GEN_HPP
#define RAND_GEN_HPP

#include "../DataStructures/graphADT.hpp"
#include "../DataStructures/adjacency_matrix.hpp"
#include "random.hpp"

#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

class Generator{
private:
	AdjacencyMatrix G;
	void generate_vertices(const unsigned long _number_of_nodes);
	bool valid_input(const unsigned long _number_of_nodes, const unsigned long _number_of_edges);
	vector<unsigned long> reservoir_sampling(const unsigned long size_subset, const unordered_set<unsigned long> potential_edges);
public:
	Generator();
	void generate_set_edges(const unsigned long _number_of_nodes, const unsigned long _number_of_edges, bool _acyclic, bool _directed, bool _self_loops);
	void generate_p_edges(const unsigned long _number_of_nodes, const float p, bool _acyclic, bool _directed, bool _self_loops);
	void generate_edge_weight(const float _min, const float _max);
	void reflect_matrix();
	GraphADT* get();
};

#endif
