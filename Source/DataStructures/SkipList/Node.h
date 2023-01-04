#pragma once

template <typename T>
class Node {
public:
	Node(const T& data);

public:
	Node<T>* m_next{ nullptr };
	Node<T>* m_previous{ nullptr };
	Node<T>* m_skip{ nullptr };

	T m_data{ };
};

#include "Source/Node_imp.h"
