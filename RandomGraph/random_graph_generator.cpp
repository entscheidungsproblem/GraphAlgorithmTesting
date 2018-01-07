#include "random_graph_generator.hpp"

#include <iostream>
#include <utility>	// For make_pair
#include <stdexcept>	// For throw std::invalid_argument
#include <random>

using std::uniform_int_distribution;
using std::uniform_real_distribution;

Generator::Generator(){
	AdjacencyMatrix _G;
	G = _G;
}

bool Generator::valid_input(const unsigned long _number_of_nodes, const unsigned long _number_of_edges){
	// Check that the graph can be created
	if (_number_of_nodes*_number_of_nodes < _number_of_edges){return false;}
	return true;
}

void Generator::generate_vertices(const unsigned long _number_of_nodes){
	// Add all nodes
	for (unsigned long i = 0; i != _number_of_nodes; ++i){
		this->G.add_vertex();
	}
}

vector<unsigned long> Generator::reservoir_sampling(const unsigned long size_subset, const unordered_set<unsigned long> potential_edges){
	Random<unsigned long> r;
	unsigned long size_set = potential_edges.size();
	if (size_subset > size_set){
		throw std::invalid_argument( "reservoir_sampling input error\n" );
	}
	// First, create a vector of the first size_subset elements
	// This is our base case
	vector<unsigned long> output(size_subset);
	unsigned long i = 0;
	for (unordered_set<unsigned long>::const_iterator it = potential_edges.cbegin(); it != potential_edges.cend(); it++){
		if (i < size_subset){
			output[i] = *it;
			i++;	
		}
		else if (i < size_set){
			unsigned long p = r.random_num<uniform_int_distribution<unsigned long>>(0, i); // i-1 maybe?
			if (p < size_subset){
				// Then randomly select the element in output to replace
				unsigned long random_index = r.random_num<uniform_int_distribution<unsigned long>>(0, size_subset-1);
				output[random_index] = *it;
			}
			i++;
		}
	}
	return output;
} 

void Generator::generate_set_edges(const unsigned long _number_of_nodes, const unsigned long _number_of_edges, bool _acyclic, bool _directed, bool _self_loops){

	if (!_directed) {_acyclic = true;}
	// Check for valid input in seperate function
	if(!valid_input(_number_of_nodes, _number_of_edges)){
		throw std::invalid_argument( "Generate_set_edges invalid input\n" );
	}

	generate_vertices(_number_of_nodes);

	unsigned long size = _number_of_nodes*_number_of_nodes;
	
	// Create a set of potential edges
	unordered_set<unsigned long> potential_edges;
	unsigned long x;
	unsigned long y;
	for (unsigned long i = 0; i < size; i++){
		x = i % _number_of_nodes;
		y = (unsigned long) i / _number_of_nodes;
		// Only add an edge to the potential set if it satisfies _self_loop and _acyclic
		if ((x > y) || (x == y && _self_loops) || (x < y && !_acyclic)){
			potential_edges.insert(i);
		}
	}
	// If self loops are not allowed, remove elements in the diagonal
	if (!_self_loops){ size -= _number_of_nodes;}
	// If acyclic, remove all elements below the diagonal
	if (_acyclic){ size -= _number_of_nodes*(_number_of_nodes-1)/2;}

	if (size < _number_of_edges){
		throw std::invalid_argument( "Generate_set_edges invalid input\n" );
	}

	// Use reservior sampling to generate _number_of_edges unique numbers between 0 and size
	vector<unsigned long> output = reservoir_sampling(_number_of_edges, potential_edges);
	for (vector<unsigned long>::iterator i = output.begin(); i != output.end(); i++){
		G.set_edge(*i);
	}
	if (_directed) {G.set_directed(true);}
}

void Generator::generate_p_edges(const unsigned long _number_of_nodes, const float p, bool _acyclic, bool _directed, bool _self_loops){
	// If the graph is undirected, only generate half of the graph or make it acyclic
	// Afterwards weights can be added, if wanted, and the matrix can be reflected to appear undirected
	if (!_directed) {_acyclic = true;}
	Random<float> r;
	generate_vertices(_number_of_nodes);

	unsigned long diagonal;
	for (unsigned long y = 0; y != _number_of_nodes; y++){
		diagonal = 0;
		if (_acyclic){
			diagonal += y;
			// If the graph does not allow self loops, add 1 to skip the diagonal 
			if (!_self_loops){
				diagonal += 1;
			}
		}
		for (unsigned long x = diagonal; x < _number_of_nodes; x++){
			// If the generated probability is less than the thresold, add an edge
			float probability = r.random_num<uniform_real_distribution<float>>(0, 1);
			if ((_self_loops || x!=y)&&(probability < p)){
				G.set_edge(y*_number_of_nodes + x);
			}
		}
	}
	if (_directed) {G.set_directed(true);}
}

void Generator::reflect_matrix(){
	unsigned long size = G.get_vertex_size();
	// Reflect each edge in the upper right triangle
	for (unsigned long y = 0; y != size; y++){
		for (unsigned long x = y; x != size; x++){
			if (G.check_edge(y*size + x)){
				G.set_edge(x*size + y, 1.0);
			}
		}
	}
}

void Generator::generate_edge_weight(const float _min, const float _max){
	Random<float> r;
	unsigned long size = G.get_vertex_size()*G.get_vertex_size();
	// Assign a random weight to each edge
	for (unsigned long i = 0; i < size; i++){
		if (G.check_edge(i)){
			float weight = r.random_num<uniform_real_distribution<float>>(_min, _max);
			G.set_edge(i, weight);
		}
	}
}

GraphADT* Generator::get(){
	return &G;
}
