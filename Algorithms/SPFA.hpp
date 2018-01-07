#ifndef SPFA_HPP
#define SPFA_HPP

#include "../DataStructures/graphADT.hpp"

#include <optional>
#include <vector>
#include <utility>      // std::pair, std::get

using std::optional;
using std::vector;


class SPFA{
public:
	vector<std::pair<float, optional<unsigned long>>> shortest_path(GraphADT* G, unsigned long start);
};

#endif
