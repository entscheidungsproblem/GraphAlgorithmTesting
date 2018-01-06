#include <fstream>
#include <stdio.h>

#include "adjacency_matrix.hpp"

#include <boost/assert.hpp>

AdjacencyMatrix::AdjacencyMatrix(){
	edges = {};
	number_of_vertices = 0;
	number_of_edges = 0;
	directed = true;
}

void AdjacencyMatrix::add_vertex(){
	// Add all of the new possible edges
	for (unsigned long i = 0; i < (2*number_of_vertices) + 1; i++){
		edges.push_back(boost::optional<float>{});
	}
	number_of_vertices++;

	BOOST_ASSERT(edges.size()==number_of_vertices*number_of_vertices);
}

bool AdjacencyMatrix::check_edge(unsigned long position){
	if (edges[position]){
		return true;
	}
	return false;
}

void AdjacencyMatrix::set_edge(unsigned long position, const float weight){
	if (!check_edge(position)){
		number_of_edges++;
	}
	edges[position] = weight;
}

float AdjacencyMatrix::get_edge(unsigned long position){
	return edges[position].get();
}

unsigned long AdjacencyMatrix::get_edge_size(){
	return number_of_edges;
}

unsigned long AdjacencyMatrix::get_vertex_size(){
	return number_of_vertices;
}

void AdjacencyMatrix::print_graph(){
	unsigned long i = 0;
	for (unsigned long j = 0; j < edges.size(); j++){
		if (check_edge(j)){
			printf("%.2f ", edges[j].get());
		}
		else{
			printf("_.__ ");
		}
		++i;
		if(i == number_of_vertices){
			printf("\n");
			i = 0;
		}
	}
}

void AdjacencyMatrix::export_dot(std::string filename, boost::container::set<unsigned long> shortest_path_tree){
	// Create file
	//std::string filename("graph");
	filename+=".dot";
	FILE *myfile = fopen (filename.c_str() , "w");
	// Create header for graph or digraph
	if (directed) fprintf(myfile, "digraph G {\n");
	else fprintf(myfile, "graph G {\n");

	// Add all edges
	for (unsigned long y = 0; y < number_of_vertices; y++){
		for (unsigned long x = 0; x < number_of_vertices; x++){
			if (check_edge(x+number_of_vertices*y)){
				fprintf(myfile, "\tx%lu -",y);
				if (directed){
					fprintf(myfile, ">");
				}
				else{
					fprintf(myfile, "-");
				}
				fprintf(myfile, "x%lu [label=%.2f,weight=%f",x,(edges[x+number_of_vertices*y]).get(),(edges[x+number_of_vertices*y]).get());
				if (shortest_path_tree.find(x+number_of_vertices*y)!=shortest_path_tree.end()){
					fprintf(myfile, ",color=red");
				}
				fprintf(myfile, "];\n");
			}
		}
	}
	fprintf(myfile, "}");
	fclose(myfile);
}

void AdjacencyMatrix::set_directed(bool _directed){
	directed = _directed;
}

bool AdjacencyMatrix::get_directed(){
	return directed;
}

unsigned long AdjacencyMatrix::get_in_degree(unsigned long finish){
	unsigned long degree = 0;
	for (unsigned long start = 0ul; start != number_of_vertices; start++){
		if (check_edge(start*number_of_vertices + finish)){
			degree++;
		}
	}
	return degree;
}

unsigned long AdjacencyMatrix::get_out_degree(unsigned long start){
	unsigned long degree = 0;
	for (unsigned long finish = 0ul; finish != number_of_vertices; finish++){
		if (check_edge(start*number_of_vertices + finish)){
			degree++;
		}
	}
	return degree;
}