#pragma once

#include <iostream>
#include <cstdint>

#include "Vertex.h"

template <typename T>
class Graph {
public:
	Graph();
	Graph(const Graph<T>& other);
	~Graph();

	void InsertVertex(const T& data);
	void InsertEdge(Vertex<T>* firstVertex, Vertex<T>* secondVertex, std::uint32_t weight);

	Vertex<T>* GetVertex(const T& data) const;
	
	Graph<T>& operator=(const Graph<T>& other);

private:
	std::vector<Vertex<T>*> m_data{ };

private:
	void CopyDataFrom(const Graph<T>& other);
	void DeleteData();
};
