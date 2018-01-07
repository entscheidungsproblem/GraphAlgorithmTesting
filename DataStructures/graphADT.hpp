#ifndef GRAPH_ADT_HPP
#define GRAPH_ADT_HPP

#include <cstdint>
#include <string>
#include <set>

using std::set;
using std::string;

class GraphADT{
protected:
	bool acyclic;
	bool directed;
	bool self_loops;
	unsigned long number_of_vertices;
	unsigned long number_of_edges;

public:
	virtual void add_vertex() = 0;
	virtual void set_edge(unsigned long position, const float weight = 1.0f) = 0;
	virtual bool check_edge(unsigned long position) = 0;
	virtual float get_edge(unsigned long position) = 0;
	virtual void print_graph() = 0;
	virtual void export_dot(string filename, set<unsigned long> shortest_path_tree) = 0;
	virtual unsigned long get_edge_size() = 0;
	virtual unsigned long get_vertex_size() = 0;
	virtual void set_directed(bool _directed) = 0;
	virtual bool get_directed() = 0;
	virtual unsigned long get_in_degree(unsigned long vertex) = 0;
	virtual unsigned long get_out_degree(unsigned long vertex) = 0;
};

#endif

