#include "doctest.h"

#include "../TravelRoutes/Route.h"

TEST_CASE("Route") {
	SUBCASE("Example") {
		std::vector<std::string> cities{ "Sofia", "Pazardzhik", "Plovdiv", "Dimitrovgrad", "StaraZagora", "NovaZagora", "Yambol", "Karnobat", "Burgas" };
		std::vector<TrainConnection> fastConnections{
			{ "Sofia", "Plovdiv" },
			{ "Plovdiv", "NovaZagora" },
			{ "Dimitrovgrad", "NovaZagora" },
			{ "StaraZagora", "Yambol" },
			{ "NovaZagora", "Burgas" }
		};
		std::queue<std::string> citiesToVisit{ };

		citiesToVisit.push("Plovdiv");
		citiesToVisit.push("StaraZagora");
		citiesToVisit.push("Yambol");

		Route route(cities, fastConnections, citiesToVisit);

		std::vector<std::string> result{ route.FindBestRoute() };
		std::vector<std::string> solution{ "Sofia", "Plovdiv", "Dimitrovgrad", "StaraZagora", "Yambol", "Karnobat", "Burgas" };

		REQUIRE_EQ(result.size(), solution.size());
		REQUIRE(result == solution);
	}
}
