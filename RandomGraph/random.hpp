#ifndef RAND_HPP
#define RAND_HPP

#include <boost/random/mersenne_twister.hpp>
#include <chrono>

template <class NumType>
class Random{
private:
	unsigned create_seed();
public:
	template <class Distribution> NumType random_num(NumType _min, NumType _max);
};

template <class NumType>
unsigned Random<NumType>::create_seed(){
	// Multiply by the 5 most siginificant unit of time available to the OS (ex nano or milli seconds)
	return (std::chrono::high_resolution_clock::now().time_since_epoch().count()%100000);
}


template <class NumType>
template <class Distribution>
NumType Random<NumType>::random_num(NumType _min, NumType _max){
	// Use the given distribution to generate a random NumType
	Distribution distribution(_min, _max);
	boost::random::mt19937 generator (create_seed());
	return distribution(generator);
}

#endif