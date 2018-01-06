#ifndef ADJ_MATRIX_HPP
#define ADJ_MATRIX_HPP

#include "graphADT.hpp"
#include <boost/container/vector.hpp>
#include <boost/container/set.hpp>
#include <boost/optional.hpp>
#include <limits>


class AdjacencyMatrix : public GraphADT{
protected:
	//unsigned long number_of_vertices;
	//unsigned long number_of_edges;
	boost::container::vector<boost::optional<float>> edges;
	bool directed;
public:
	AdjacencyMatrix();
	void add_vertex() override;
	void set_edge(unsigned long position, float weight = 1.0f) override;
	bool check_edge(unsigned long position) override;
	float get_edge(unsigned long position) override;
	void print_graph() override;
	void export_dot(std::string filename, boost::container::set<unsigned long> shortest_path_tree= {}) override;
	unsigned long get_edge_size() override;
	unsigned long get_vertex_size() override;
	void set_directed(bool _directed) override;
	bool get_directed() override;
	unsigned long get_in_degree(unsigned long vertex) override;
	unsigned long get_out_degree(unsigned long vertex) override;
};

#endif