#ifndef SSSP_HPP
#define SSSP_HPP

#include "../DataStructures/graphADT.hpp"

#include <set>
#include <vector>
#include <optional>

#include <utility>      
#include <chrono>
#include <type_traits>

using std::vector;
using std::set;
using std::optional;

class SSSP{
private:
	GraphADT* G;
	unsigned long start;
	vector<vector<std::pair<float, optional<unsigned long>>>> alg_data;
	
	bool timing;
	vector<unsigned long> timing_results;

	template <class Algorithm>
	void run_SSSP();

	template <class Algorithm1, class Algorithm2, class... Algorithms>
	void run_SSSP();

public:
	void setup(GraphADT* G, unsigned long start);

	template <class Algorithm, class... Algorithms>
	vector<set<unsigned long>> run(bool timing = false);

	vector<unsigned long> get_timing_results();
};

void SSSP::setup(GraphADT* _G, unsigned long _start){
	G=_G;
	start = _start;
	timing_results = {};
	alg_data = {};
}


template <class Algorithm>
void SSSP::run_SSSP(){
	long diff;
	vector<std::pair<float, optional<unsigned long>>> _input;
	if (timing){
		// Time the algorithm
		auto t1 = std::chrono::high_resolution_clock::now();
		Algorithm alg;
		_input = alg.shortest_path(G, start);
		auto t2 = std::chrono::high_resolution_clock::now();
		diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

		// convert to unsigned long and add to results
		timing_results.push_back(static_cast<std::make_unsigned<decltype(diff)>::type>(diff));
		// BOOST_ASSERT(_input.size() == G->get_vertex_size());
		alg_data.push_back(_input);
	}
	else{
		// No timer, so just run and add to results
		Algorithm alg;
		vector<std::pair<float, optional<unsigned long>>> _input = alg.shortest_path(G, start);
		// BOOST_ASSERT(_input.size() == G->get_vertex_size());
		alg_data.push_back(_input);
	}
	
}

template <class Algorithm1, class Algorithm2, class... Algorithms>
void SSSP::run_SSSP(){
	// Use tail recursion to unroll the ellipsis
	run_SSSP<Algorithm1>();
	run_SSSP<Algorithm2,Algorithms...>();
}


template <class Algorithm, class... Algorithms>
vector<set<unsigned long>> SSSP::run(bool _timing){
	// Run the algorithms
	timing = _timing;
	run_SSSP<Algorithm, Algorithms...>();
	// Initialize the output (vector of sets of edges in shortest-path(SP) tree) and the first empty set
	vector<set<unsigned long>> output = {};
	set<unsigned long> empty = {};
	output.push_back(empty);
	// Add the SP tree of the first algorithm
	// BOOST_ASSERT(alg_data[0].size() == G->get_vertex_size());
	for (unsigned long i = 0ul; i != alg_data[0].size(); i++){
		if (std::get<1>(alg_data[0][i])){
			unsigned long vertex = std::get<1>(alg_data[0][i]).value() * G->get_vertex_size() + i;
			output[0].emplace(vertex);
		}
	}

	// For the remaining algorithms, add the their SP trees
	for (unsigned long i = 1ul; i != alg_data.size(); i++){
		// BOOST_ASSERT(alg_data[i-1].size() == alg_data[i].size());
		output.push_back(set<unsigned long> {});
		for (unsigned long j = 0ul; j != alg_data[i-1].size(); j++){
			if (std::get<1>(alg_data[i][j])){
				unsigned long vertex = std::get<1>(alg_data[i][j]).value() * G->get_vertex_size() + j;
				output[i].emplace(vertex);
			}
		}	

		// BOOST_ASSERT(output[i].size() == output[i-1].size());	
	}
	return output;
}

vector<unsigned long> SSSP::get_timing_results(){
	return timing_results;
}

#endif
