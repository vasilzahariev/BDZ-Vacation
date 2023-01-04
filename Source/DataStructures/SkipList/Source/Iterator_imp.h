#pragma once

#include "../Iterator.h"

template <typename T>
Iterator<T>::Iterator(Node<T>* node) : m_node(node) {}

template<typename T>
inline Iterator<T>& Iterator<T>::operator++() {
	m_node = m_node->m_next;

	return *this;
}
template<typename T>
inline Iterator<T> Iterator<T>::operator++(int) {
	Iterator<T> temp = *this;

	++(*this);

	return temp;
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator--() {
	m_node = m_node->m_previous;

	return *this;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--(int) {
	Iterator<T> temp = *this;

	--(*this);
	
	return temp;
}

template<typename T>
inline Node<T>* Iterator<T>::operator->() {
	return m_node;
}

template<typename T>
inline T& Iterator<T>::operator*() {
	return m_node->m_data;
}

template<typename T>
inline Iterator<T> Iterator<T>::Skip() {
	if (!m_node->m_skip) {
		return *this;
	}

	return Iterator<T>(m_node->m_skip);
}

template<typename T>
inline bool Iterator<T>::operator==(const Iterator<T>& other) {	
	return m_node == other.m_node;
}

template<typename T>
inline bool Iterator<T>::operator!=(const Iterator<T>& other) {
	return !(*this == other);
}
