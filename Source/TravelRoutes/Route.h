#pragma once

#include <string>
#include <map>
#include <vector>
#include <queue>

#include "../DataStructures/SkipList/SkipList.h"
#include "TrainConnection.h"

class Route {
public:
	Route(const std::vector<std::string>& cities, const std::vector<TrainConnection>& fastConnections,
		  const std::queue<std::string>& citiesToVisit);

	std::vector<std::string> FindBestRoute();

private:
	std::map<std::string, std::size_t> m_cityOrder{ };
	std::queue<std::string> m_citiesToVisit{ };
	SkipList<std::string> m_cities{ };
};
