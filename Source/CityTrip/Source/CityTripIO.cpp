#include "../CityTripIO.h"

CityTrip CityTripIO::Read(std::istream& in) {
    std::size_t nDestinations{ };
    std::size_t nConnections{ };
    std::vector<std::string> destinations{ };
    std::vector<EdgeConnection> connections{ };

    in >> nDestinations >> nConnections;

    for (std::size_t index{ 0 }; index < nConnections; ++index) {
        std::string first{ };
        std::string second{ };
        std::uint32_t mins{ };

        in >> first >> second >> mins;

        if (std::find(destinations.begin(), destinations.end(), first) == destinations.end()) {
            destinations.push_back(first);
        }

        if (std::find(destinations.begin(), destinations.end(), second) == destinations.end()) {
            destinations.push_back(second);
        }

        connections.push_back(EdgeConnection{ first, second, mins });
    }

    std::uint32_t maxMins{ };

    in >> maxMins;

    return CityTrip(destinations, connections, maxMins);
}

void CityTripIO::Write(std::ostream& out, const std::vector<std::string>& result) {
    for (std::string dest : result) {
        out << dest << ' ';
    }

    out << std::endl;
}
