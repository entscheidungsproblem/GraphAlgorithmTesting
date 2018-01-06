#ifndef GRAPH_CONVERT_HPP
#define GRAPH_CONVERT_HPP

#include "graphADT.hpp"


class Converter{
private:
	GraphADT* G;
public:
	Converter(GraphADT* _G);
	template <class OutGraph> GraphADT* convert();
};

Converter::Converter(GraphADT* _G){
	G=_G;
}

template <class OutGraph>
GraphADT* Converter::convert(){
	OutGraph* out = new OutGraph();
	// First, add vertices
	unsigned long size = G->get_vertex_size();
	for (unsigned long i = 0ul; i != size; i++){
		out->add_vertex();
	}
	// Add all existing edges
	for (unsigned long i = 0ul; i != size*size; i++){
		if (G->check_edge(i)){
			out->set_edge(i, G->get_edge(i));
		}
	}
	return out;
}

#endif