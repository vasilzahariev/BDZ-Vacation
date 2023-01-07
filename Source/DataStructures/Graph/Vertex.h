#pragma once

#include <vector>

#include "Edge.h"

template <typename T>
class Vertex {
public:
	Vertex(const T& data);

public:
	std::vector<Edge<Vertex<T>>> m_edges{ };
	
	T m_data{ };
};

#include "Source/Vertex_imp.h"
