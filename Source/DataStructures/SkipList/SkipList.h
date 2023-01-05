#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include "Node.h"
#include "Iterator.h"

template <typename T>
class SkipList {
public:
	SkipList();
	SkipList(T* arrayOfData, std::size_t sizeOfArrayOfData);
	SkipList(const std::vector<std::string>& vectorOfData);
	SkipList(const SkipList<T>& other);
	~SkipList();

	bool Empty() const;
	std::size_t Size() const;

	void Insert(const T& data, std::size_t position);
	void Erase(std::size_t position);

	void PushBack(const T& data);
	void PushFront(const T& data);

	void PopBack();
	void PopFront();

	void AddSkipToNodeWithVal(const T& nodeVal, const T& skipToVal);

	T& At(std::size_t position);

	Iterator<T> begin() const;
	Iterator<T> end() const;

	SkipList<T>& operator=(const SkipList<T>& other);

private:
	Node<T>* m_front{ nullptr };
	Node<T>* m_back{ nullptr };

	std::size_t nSize{ 0 };

private:
	void DeleteData();
	void CopyDataFrom(const SkipList<T>& other);

	void Pusher(Node<T>* node, std::function<void(Node<T>*)> push);

	Node<T>* FindNodeWithValue(const T& val);
};

#include "Source/SkipList_imp.h"
