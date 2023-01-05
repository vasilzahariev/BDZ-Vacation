#include "../RouteIO.h"

Route RouteIO::Read(std::istream& in) {
	if (!in.good()) {
		throw std::runtime_error("Stream is not good");
	}

	std::vector<std::string> cities{ };
	std::vector<TrainConnection> connections{ };
	std::queue<std::string> citiesToVisit{ };

	ReadCities(in, cities);
	ReadFastConnections(in, connections);
	ReadCitiesToVisit(in, citiesToVisit);

	return Route(cities, connections, citiesToVisit);
}

void RouteIO::Write(std::ostream& out, const std::vector<std::string>& result) {
	std::string output{ "" };

	for (std::string city : result) {
		output += city + ' ';
	}

	out << output;
}

void RouteIO::ReadCities(std::istream& in, std::vector<std::string>& cities) {
	std::size_t citiesToRead{ 0 };
	std::string input{ "" };

	in >> citiesToRead;

	for (std::size_t index{ 0 }; index < citiesToRead; ++index) {
		in >> input;

		cities.push_back(input);
	}
}

void RouteIO::ReadFastConnections(std::istream& in, std::vector<TrainConnection>& fastConnections) {
	std::size_t connectionsToRead{ 0 };
	std::string input{ "" };

	in >> connectionsToRead;

	for (std::size_t index{ 0 }; index < connectionsToRead; ++index) {
		TrainConnection connection{ };

		in >> connection.m_fromStation >> connection.m_toStation;

		fastConnections.push_back(connection);
	}
}

void RouteIO::ReadCitiesToVisit(std::istream& in, std::queue<std::string>& citiesToVisit) {
	std::size_t toRead{ 0 };
	std::string input{ "" };

	in >> toRead;

	for (std::size_t index{ 0 }; index < toRead; ++index) {
		in >> input;

		citiesToVisit.push(input);
	}
}
