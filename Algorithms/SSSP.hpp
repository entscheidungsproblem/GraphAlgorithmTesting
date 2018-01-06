#ifndef SSSP_HPP
#define SSSP_HPP

#include "../DataStructures/graphADT.hpp"

#include <boost/container/set.hpp>
#include <boost/container/vector.hpp>
#include <boost/optional.hpp>
#include <boost/assert.hpp>

#include <utility>      
#include <chrono>
#include <type_traits>


class SSSP{
private:
	GraphADT* G;
	unsigned long start;
	boost::container::vector<boost::container::vector<std::pair<float, boost::optional<unsigned long>>>> alg_data;
	
	bool timing;
	boost::container::vector<unsigned long> timing_results;

	template <class Algorithm>
	void run_SSSP();

	template <class Algorithm1, class Algorithm2, class... Algorithms>
	void run_SSSP();

public:
	void setup(GraphADT* G, unsigned long start);

	template <class Algorithm, class... Algorithms>
	boost::container::vector<boost::container::set<unsigned long>> run(bool timing = false);

	boost::container::vector<unsigned long> get_timing_results();
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
	boost::container::vector<std::pair<float, boost::optional<unsigned long>>> _input;
	if (timing){
		// Time the algorithm
		auto t1 = std::chrono::high_resolution_clock::now();
		Algorithm alg;
		_input = alg.shortest_path(G, start);
		auto t2 = std::chrono::high_resolution_clock::now();
		diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

		// convert to unsigned long and add to results
		timing_results.push_back(static_cast<std::make_unsigned<decltype(diff)>::type>(diff));
		BOOST_ASSERT(_input.size() == G->get_vertex_size());
		alg_data.push_back(_input);
	}
	else{
		// No timer, so just run and add to results
		Algorithm alg;
		boost::container::vector<std::pair<float, boost::optional<unsigned long>>> _input = alg.shortest_path(G, start);
		BOOST_ASSERT(_input.size() == G->get_vertex_size());
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
boost::container::vector<boost::container::set<unsigned long>> SSSP::run(bool _timing){
	// Run the algorithms
	timing = _timing;
	run_SSSP<Algorithm, Algorithms...>();
	// Initialize the output (vector of sets of edges in shortest-path(SP) tree) and the first empty set
	boost::container::vector<boost::container::set<unsigned long>> output = {};
	boost::container::set<unsigned long> empty = {};
	output.push_back(empty);
	// Add the SP tree of the first algorithm
	BOOST_ASSERT(alg_data[0].size() == G->get_vertex_size());
	for (unsigned long i = 0ul; i != alg_data[0].size(); i++){
		if (std::get<1>(alg_data[0][i])){
			unsigned long vertex = std::get<1>(alg_data[0][i]).get() * G->get_vertex_size() + i;
			output[0].emplace(vertex);
		}
	}

	// For the remaining algorithms, add the their SP trees
	for (unsigned long i = 1ul; i != alg_data.size(); i++){
		BOOST_ASSERT(alg_data[i-1].size() == alg_data[i].size());
		output.push_back(boost::container::set<unsigned long> {});
		for (unsigned long j = 0ul; j != alg_data[i-1].size(); j++){
			if (std::get<1>(alg_data[i][j])){
				unsigned long vertex = std::get<1>(alg_data[i][j]).get() * G->get_vertex_size() + j;
				output[i].emplace(vertex);
			}
		}	

		BOOST_ASSERT(output[i].size() == output[i-1].size());	
	}
	return output;
}

boost::container::vector<unsigned long> SSSP::get_timing_results(){
	return timing_results;
}

#endif