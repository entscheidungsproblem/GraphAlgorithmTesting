#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../DataStructures/graphADT.hpp"

#include <boost/optional.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/set.hpp>
#include <utility>      // std::pair, std::get

class Dijkstra{
public:
	boost::container::vector<std::pair<float, boost::optional<unsigned long>>> shortest_path(GraphADT* G, unsigned long start);
};

#endif