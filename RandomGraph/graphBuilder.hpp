#ifndef GRAPH_BUILD_HPP
#define GRAPH_BUILD_HPP

#include "../DataStructures/graphADT.hpp"
#include "../DataStructures/adjacency_matrix.hpp"
#include "random_graph_generator.hpp"

#include <boost/tuple/tuple.hpp>


class Builder{
protected:
	bool acyclic;
	bool directed;
	bool self_loops;
	unsigned long number_of_vertices;
	unsigned long number_of_edges;
	float edge_probability;
	bool probabilistic;
	float min;
	float max;
	bool weighted;

public:
	Builder ();
	Builder& setAcyclic( const bool _acyclic );
	Builder& setDirected( const bool _directed );
	Builder& setSelfLoops( const bool _self_loops );
	Builder& setNumberVertices( const unsigned long _number_of_vertices );
	Builder& setNumberEdges( const unsigned long _number_of_edges );
	Builder& setEdgeProbability( const float _edge_probability );
	Builder& setweight( const float _min, const float _max );
	GraphADT* build();
};

#endif