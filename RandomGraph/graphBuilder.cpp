#include "graphBuilder.hpp"

//Constructor default values
Builder::Builder (){
	acyclic = false;
	directed = true;
	self_loops = false;
	number_of_vertices = 5;
	number_of_edges = 10;
	probabilistic = false;
	weighted = false;
}

Builder& Builder::setAcyclic( const bool _acyclic ){ acyclic = _acyclic; return *this; }
Builder& Builder::setDirected( const bool _directed ){ directed = _directed; return *this; }
Builder& Builder::setSelfLoops( const bool _self_loops ){ self_loops = _self_loops; return *this; }
Builder& Builder::setNumberVertices( const unsigned long _number_of_vertices ){ number_of_vertices = _number_of_vertices; return *this; }

Builder& Builder::setNumberEdges( const unsigned long _number_of_edges ){ 
	this->number_of_edges = _number_of_edges;
	this->probabilistic = false;
	return *this; 
}

Builder& Builder::setEdgeProbability( const float _edge_probability ){ 
	this->edge_probability = _edge_probability;
	this->probabilistic = true;
	return *this; 
}

Builder& Builder::setweight( const float _min, const float _max ){ 
	this->min = _min;
	this->max = _max;
	weighted = true;
	return *this; 
}

GraphADT* Builder::build(){
	Generator* gen = new Generator();
	// 2 constructors for probabilistic or set edges
	if (probabilistic) {
		gen->generate_p_edges(number_of_vertices, edge_probability, acyclic, directed, self_loops);
	}
	else {
		gen->generate_set_edges(number_of_vertices, number_of_edges, acyclic, directed, self_loops);
	}
	if (weighted){
		gen->generate_edge_weight(min, max);
		if (!directed){ gen->reflect_matrix(); }
	}
	return gen->get();
}