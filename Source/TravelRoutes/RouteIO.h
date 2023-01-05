#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Route.h"

class RouteIO {
public:
	static Route Read(std::istream& in);
	
	static void Write(std::ostream& out, const std::vector<std::string>& result);

private:
	static void ReadCities(std::istream& in, std::vector<std::string>& cities);
	static void ReadFastConnections(std::istream& in, std::vector<TrainConnection>& fastConnections);
	static void ReadCitiesToVisit(std::istream& in, std::queue<std::string>& citiesToVisit);
};
