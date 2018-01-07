#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../DataStructures/graphADT.hpp"

#include <optional>
#include <vector>
#include <set>
#include <utility>      // std::pair, std::get

using std::optional;
using std::vector;
using std::set;

class Dijkstra{
public:
	vector<std::pair<float, optional<unsigned long>>> shortest_path(GraphADT* G, unsigned long start);
};

#endif
