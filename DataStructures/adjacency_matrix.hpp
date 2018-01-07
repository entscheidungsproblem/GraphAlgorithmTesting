#ifndef ADJ_MATRIX_HPP
#define ADJ_MATRIX_HPP

#include "graphADT.hpp"
#include <vector>
#include <set>
#include <optional>
#include <limits>

using std::set;
using std::vector;
using std::optional;
using std::string;



class AdjacencyMatrix : public GraphADT{
protected:
	//unsigned long number_of_vertices;
	//unsigned long number_of_edges;
	vector<optional<float>> edges;
	bool directed;
public:
	AdjacencyMatrix();
	void add_vertex() override;
	void set_edge(unsigned long position, float weight = 1.0f) override;
	bool check_edge(unsigned long position) override;
	float get_edge(unsigned long position) override;
	void print_graph() override;
	void export_dot(string filename, set<unsigned long> shortest_path_tree= {}) override;
	unsigned long get_edge_size() override;
	unsigned long get_vertex_size() override;
	void set_directed(bool _directed) override;
	bool get_directed() override;
	unsigned long get_in_degree(unsigned long vertex) override;
	unsigned long get_out_degree(unsigned long vertex) override;
};

#endif
