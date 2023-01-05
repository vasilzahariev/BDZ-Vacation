#include "../Route.h"

Route::Route(const std::vector<std::string>& cities, const std::vector<TrainConnection>& fastConnections,
			 const std::queue<std::string>& citiesToVisit)
	: m_cities(cities), m_citiesToVisit(citiesToVisit) {
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

		if (!m_citiesToVisit.empty() && m_cities.GetPositionOfValue(*skipIter) <= m_cities.GetPositionOfValue(m_citiesToVisit.front())) {
			iter = skipIter;
		}
		else {
			iter++;
		}
	}
	
	return result;
}
