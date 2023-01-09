#include "doctest.h"
#include "../CityTrip/CityTrip.h"

TEST_CASE("CityTrip") {
	SUBCASE("Example") {
		std::vector<std::string> destinations{
			"Railstation",
			"ArtGallery",
			"RomanStadium",
			"DzhumayaSquare",
			"HistoricalMuseum",
			"AntiqueTheatre"
		};

		std::vector<EdgeConnection> connections{
			EdgeConnection{ "Railstation", "ArtGallery", 26 },
			EdgeConnection{ "Railstation", "RomanStadium", 20 },
			EdgeConnection{ "ArtGallery", "DzhumayaSquare", 5 },
			EdgeConnection{ "ArtGallery", "HistoricalMuseum", 14 },
			EdgeConnection{ "ArtGallery", "AntiqueTheatre", 7 },
			EdgeConnection{ "RomanStadium", "DzhumayaSquare", 2 },
			EdgeConnection{ "DzhumayaSquare", "HistoricalMuseum", 18 },
			EdgeConnection{ "HistoricalMuseum", "AntiqueTheatre", 12 }
		};

		CityTrip trip(destinations, connections, 68);

		std::vector<std::string> result{ trip.FindBestRoute() };

		REQUIRE_EQ(result.size(), 7);
	}

	SUBCASE("Example 2") {
		std::vector<std::string> destinations{
			"Railstation",
			"B",
			"C"
		};

		std::vector<EdgeConnection> connections{
			EdgeConnection{ "Railstation", "B", 50 },
			EdgeConnection{ "Railstation", "C", 50 },
			EdgeConnection{ "B", "C", 5 },
		};

		CityTrip trip(destinations, connections, 60);

		std::vector<std::string> result{ trip.FindBestRoute() };

		REQUIRE_EQ(result.size(), 1);
		REQUIRE_EQ(result[0], "Railstation");
	}
}
