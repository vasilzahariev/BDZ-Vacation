#pragma once

#include "../Graph.h"

template <typename T>
Graph<T>::Graph() {}

template<typename T>
inline Graph<T>::Graph(const Graph<T>& other) {
	try {
		CopyDataFrom(other);
	}
	catch (...) {
		DeleteData();
	}
}

template<typename T>
inline Graph<T>::~Graph() {
	DeleteData();
}

template<typename T>
inline void Graph<T>::InsertVertex(const T& data) {
	m_data.push_back(new Vertex<T>(data));
}

template<typename T>
inline void Graph<T>::InsertEdge(Vertex<T>* firstVertex, Vertex<T>* secondVertex, std::uint32_t weight) {
	firstVertex->m_edges.push_back(Edge<Vertex<T>>{ secondVertex, weight});
	secondVertex->m_edges.push_back(Edge<Vertex<T>>{ firstVertex, weight});
}

template<typename T>
inline Vertex<T>* Graph<T>::GetVertex(const T& data) const {
	for (Vertex<T>* vertex : m_data) {
		if (vertex->m_data == data) {
			return vertex;
		}
	}

	throw std::logic_error("There is no such vertex");
}

template<typename T>
inline Graph<T>& Graph<T>::operator=(const Graph<T>& other) {
	if (this != &other) {
		DeleteData();
		CopyDataFrom(other);
	}

	return *this;
}

template<typename T>
inline void Graph<T>::CopyDataFrom(const Graph<T>& other) {
	for (auto vertex : other.m_data) {
		InsertVertex(vertex->m_data);
	}

	for (auto vertex : other.m_data) {
		for (auto edge : vertex->m_edges) {
			vertex->m_edges.push_back(Edge<Vertex<T>>{ GetVertex(edge.m_to->m_data), edge.m_weight });
		}
	}
}

template<typename T>
inline void Graph<T>::DeleteData() {
	// TODO
}
