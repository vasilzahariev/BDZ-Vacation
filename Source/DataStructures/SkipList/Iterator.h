#pragma once

#include "Node.h"

template <typename T>
class Iterator {
public:
	Iterator(Node<T>* node);

	Iterator<T>& operator++();
	Iterator<T> operator++(int);

	Iterator<T>& operator--();
	Iterator<T> operator--(int);

	Node<T>* operator->();

	T& operator*();

	Iterator<T> Skip();

	bool operator==(const Iterator<T>& other);
	bool operator!=(const Iterator<T>& other);

private:
	Node<T>* m_node{ nullptr };
};

#include "Source/Iterator_imp.h"
