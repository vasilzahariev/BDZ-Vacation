#pragma once

#include <string>
#include <algorithm>

#include "../DataStructures/Graph/Graph.h"
#include "EdgeConnection.h"

class CityTrip {
public:
	CityTrip(const std::vector<std::string>& destinations, const std::vector<EdgeConnection>& connections, std::uint32_t maxMins);

	std::vector<std::string> FindBestRoute();

private:
	Graph<std::string> m_graph{  };
	std::uint32_t m_maxMins{ 0 };

private:
	void FindAllPossiblePaths(Vertex<std::string>* iter, std::uint32_t mins, std::vector<std::vector<std::string>>& paths, std::vector<std::string>& path);

	std::uint32_t CountDestinations(const std::vector<std::string>& destinations) const;
};
