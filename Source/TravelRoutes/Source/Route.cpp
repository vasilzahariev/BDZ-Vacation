#include "../Route.h"

Route::Route(const std::vector<std::string>& cities, const std::vector<TrainConnection>& fastConnections,
			 const std::queue<std::string>& citiesToVisit)
	: m_cities(cities), m_citiesToVisit(citiesToVisit) {
	for (std::size_t index{ 0 }; index < cities.size(); ++index) {
		m_cityOrder.insert({ cities[index], index + 1 });
	}

	for (TrainConnection fastTravel : fastConnections) {
		m_cities.AddSkipToNodeWithVal(fastTravel.m_fromStation, fastTravel.m_toStation);
	}
}

std::vector<std::string> Route::FindBestRoute() {
	Iterator<std::string> iter{ m_cities.begin() };
	std::vector<std::string> result{ };

	while (iter != m_cities.end()) {
		result.push_back(*iter);

		if (!m_citiesToVisit.empty() && *iter == m_citiesToVisit.front()) {
			m_citiesToVisit.pop();
		}

		Iterator<std::string> skipIter = iter.Skip();

		if (!m_citiesToVisit.empty() && m_cityOrder.at(*skipIter) <= m_cityOrder.at(m_citiesToVisit.front())) {
			iter = skipIter;
		}
		else {
			iter++;
		}
	}
	
	return result;
}
