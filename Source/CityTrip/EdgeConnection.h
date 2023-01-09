#pragma once

#include <string>

struct EdgeConnection {
public:
	std::string m_firstDestination{ };
	std::string m_secondDestination{ };
	std::uint32_t m_mins{ };
};
