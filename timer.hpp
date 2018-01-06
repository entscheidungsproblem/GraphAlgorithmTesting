#ifndef TIMER_SSSP_HPP
#define TIMER_SSSP_HPP

#include <chrono>


#include "RandomGraph/graphBuilder.hpp"

#include "DataStructures/graph_converter.hpp"

#include "Algorithms/SSSP.hpp"
#include <iostream>

class TimeSSSP{
private:
	Builder* B;
	SSSP* alg;
	boost::container::vector<boost::container::vector<unsigned long>> results;

	template <class Algorithm, class... Algorithms>
	void run_single();

public:
	TimeSSSP(Builder* _B);

	template <class Algorithm, class... Algorithms>
	void run(unsigned long num);

	boost::container::vector<float> average();
};

TimeSSSP::TimeSSSP(Builder* _B){
	B=_B;
	alg = new SSSP();
}

template <class Algorithm, class... Algorithms>
void TimeSSSP::run_single(){
	GraphADT* G = B->build();
	//Converter* c = new Converter(_G);
	//GraphADT* G = c->convert<AdjacencyList>();
	alg->setup(G, 0ul);
	alg->run<Algorithm, Algorithms...>(true);
	boost::container::vector<unsigned long> single_result = alg->get_timing_results();

	results.push_back(single_result);

	BOOST_ASSERT(single_result.size() == sizeof...(Algorithms) + 1);
}

template <class Algorithm, class... Algorithms>
void TimeSSSP::run(unsigned long cases){
	for (unsigned counter = 0ul; counter != cases; counter++){
		run_single<Algorithm, Algorithms...>();
	}
	boost::container::vector<float> avg = average();
}

boost::container::vector<float> TimeSSSP::average(){
	boost::container::vector<float> out = {};
	unsigned long size = results[0].size();	// Number of algorithms
	// Set up
	for (unsigned long i = 0ul; i != size; i++){	// Iterate over number of algorithms
		out.push_back(0);
	}

	// Add contents
	for (unsigned long i = 0ul; i != results.size(); i++){ // Iterate over number of test cases
		for (unsigned long j = 0ul; j != size; j++){	// Iterate over number of algorithms
			out[j] += results[i][j];
		}
	}

	//Divide by size
	for (unsigned long i = 0ul; i != size; i++){	// Iterate over number of algorithms
		out[i] /= results.size();
	}
	return out;
}





#endif
