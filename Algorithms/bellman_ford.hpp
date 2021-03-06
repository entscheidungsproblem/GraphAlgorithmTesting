#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "../DataStructures/graphADT.hpp"

#include <optional>
#include <vector>
#include <utility>      // std::pair, std::get

using std::vector;
using std::optional;

class BellmanFord{
public:
	vector<std::pair<float, optional<unsigned long>>> shortest_path(GraphADT* G, unsigned long start);
};

#endif
