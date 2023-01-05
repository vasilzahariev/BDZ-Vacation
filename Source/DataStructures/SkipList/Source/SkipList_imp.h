#pragma once

#include "../SkipList.h"

template <typename T>
SkipList<T>::SkipList() {}

template <typename T>
SkipList<T>::SkipList(T* arrayOfData, std::size_t sizeOfArrayOfData) {
	for (std::size_t index{ 0 }; index < sizeOfArrayOfData; ++index) {
		PushBack(arrayOfData[index]);
	}
}

template<typename T>
inline SkipList<T>::SkipList(const std::vector<std::string>& vectorOfData) {
	for (std::size_t index{ 0 }; index < vectorOfData.size(); ++index) {
		PushBack(vectorOfData[index]);
	}
}

template<typename T>
inline SkipList<T>::SkipList(const SkipList<T>& other) {
	try {
		CopyDataFrom(other);
	}
	catch (...) {
		DeleteData();
	}
}

template<typename T>
inline SkipList<T>::~SkipList() {
	DeleteData();
}

template<typename T>
inline bool SkipList<T>::Empty() const {
	return m_front == nullptr;
}

template<typename T>
inline std::size_t SkipList<T>::Size() const {
	return nSize;
}

template<typename T>
inline void SkipList<T>::Insert(const T& data, std::size_t position) {
	if (position < 0 || position > nSize) {
		throw std::length_error("Invalid index");
	}

	if (position == 0) {
		PushFront(data);

		return;
	}
	else if (position == nSize) {
		PushBack(data);

		return;
	}

	Node<T>* node{ new Node<T>(data) };
	
	Node<T>* iter{ m_front };
	std::size_t index{ 1 };

	while (iter && index < position) {
		iter = iter->m_next;

		++index;
	}

	if (index != position) {
		throw std::length_error("Invalid index");
	}

	Node<T>* oldNext = iter->m_next;

	node->m_previous = iter;
	node->m_next = oldNext;
	if (oldNext->m_previous) {
		oldNext->m_previous = node;
	}
	iter->m_next = node;

	++nSize;
}

template<typename T>
inline void SkipList<T>::Erase(std::size_t position) {
	if (position < 0 || position >= nSize) {
		throw std::length_error("Index out of bounds!");
	}

	if (position == 0) {
		PopFront();

		return;
	}
	else if (position == nSize - 1) {
		PopBack();

		return;
	}

	Node<T>* iter{ m_front->m_next };
	std::size_t index{ 1 };

	while (iter && index < position) {
		iter = iter->m_next;
		++index;
	}

	iter->m_previous->m_next = iter->m_next;
	iter->m_next->m_previous = iter->m_previous;

	delete iter;
	iter = nullptr;

	--nSize;
}

template<typename T>
inline void SkipList<T>::PushBack(const T& data) {
	Node<T>* node = new Node<T>(data);

	Pusher(node, [this](Node<T>* node) -> void {
		node->m_previous = m_back;
		m_back->m_next = node;

		m_back = node;
	});
}

template<typename T>
inline void SkipList<T>::PushFront(const T& data) {
	Node<T>* node = new Node<T>(data);

	Pusher(node, [this](Node<T>* node) -> void {
		node->m_next = m_front;
		m_front->m_previous = node;

		m_front = node;
	});
}

template<typename T>
inline void SkipList<T>::PopBack() {
	if (Empty()) {
		throw std::logic_error("Trying to remove an element from an empty LinkedList!");
	}
	else if (nSize == 1) {
		delete m_front;
		m_front = m_back = nullptr;
	}
	else {
		Node<T>* toDelete{ m_back };

		m_back->m_previous->m_next = nullptr;
		m_back = m_back->m_previous;

		delete toDelete;
	}

	--nSize;
}

template<typename T>
inline void SkipList<T>::PopFront() {
	if (Empty()) {
		throw std::logic_error("Trying to remove an element from an empty LinkedList!");
	}
	else if (nSize == 1) {
		delete m_front;
		m_front = m_back = nullptr;
	}
	else {
		Node<T>* toDelete{ m_front };

		m_front->m_next->m_previous = nullptr;
		m_front = m_front->m_next;

		delete toDelete;
	}

	--nSize;
}

template<typename T>
inline void SkipList<T>::AddSkipToNodeWithVal(const T& nodeVal, const T& skipToVal) {
	Node<T>* node{ FindNodeWithValue(nodeVal)};

	node->m_skip = FindNodeWithValue(skipToVal);
}

template<typename T>
inline std::size_t SkipList<T>::GetPositionOfValue(const T& val) {
	std::size_t position{ 1 };

	for (T elem : *this) {
		if (elem == val) {
			return position;
		}

		++position;
	}

	throw std::logic_error("There is no such element in the SkipList");
}

template<typename T>
inline T& SkipList<T>::At(std::size_t position) {
	if (position < 0 || position >= nSize) {
		throw std::length_error("Invalid index");
	}

	Node<T>* iter{ m_front };
	std::size_t index{ 0 };

	while (iter && index < position) {
		iter = iter->m_next;
		++index;
	}

	if (index != position) {
		throw std::length_error("Invalid index");
	}

	return iter->m_data;
}

template<typename T>
inline Iterator<T> SkipList<T>::begin() const {
	return Iterator<T>(m_front);
}

template<typename T>
inline Iterator<T> SkipList<T>::end() const {
	return Iterator<T>(m_back->m_next);
}

template<typename T>
inline SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other) {
	if (this != &other) {
		DeleteData();
		CopyDataFrom(other);
	}

	return *this;
}

template<typename T>
inline void SkipList<T>::DeleteData() {	
	while (!Empty()) {
		PopBack();
	}
}

template<typename T>
inline void SkipList<T>::CopyDataFrom(const SkipList<T>& other) {
	if (other.Empty()) {
		return;
	}

	for (T iter : other) {
		PushBack(iter);
	}
}

template<typename T>
inline void SkipList<T>::Pusher(Node<T>* node, std::function<void(Node<T>*)> push) {
	++nSize;

	if (Empty()) {
		m_front = m_back = node;

		return;
	}

	push(node);
}

template<typename T>
inline Node<T>* SkipList<T>::FindNodeWithValue(const T& val) {
	Node<T>* iter = m_front;

	while (iter) {
		if (iter->m_data == val) {
			return iter;
		}

		iter = iter->m_next;
	}

	throw std::logic_error("Invalid searched value!");
}
