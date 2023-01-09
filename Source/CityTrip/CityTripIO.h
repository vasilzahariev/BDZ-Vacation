#pragma once

#include <iostream>
#include "CityTrip.h"

class CityTripIO {
public:
	static CityTrip Read(std::istream& in);
	static void Write(std::ostream& out, const std::vector<std::string>& result);

private:
	//
};
