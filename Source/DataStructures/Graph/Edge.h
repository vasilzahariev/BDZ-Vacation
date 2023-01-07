#pragma once

#include <cstdint>

template <typename NodeT>
class Edge {
public:
	NodeT* m_to{ nullptr };
	std::uint32_t m_weight{ 0 };
};
