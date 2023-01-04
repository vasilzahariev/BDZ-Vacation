#include "doctest.h"

#include "../DataStructures/SkipList/SkipList.h"

TEST_CASE("SkipList of integers") {	
	SUBCASE("The SkipList should be empty when created") {
		SkipList<int> list;
		
		REQUIRE(list.Empty());
		REQUIRE_EQ(list.Size(), 0);
	}

	SUBCASE("The SkipList should add the array elements") {
		constexpr std::size_t ARR_SIZE{ 5 };
		int* arr{ new int[ARR_SIZE] { 1, 2, 3, 4, 5 } };
		
		SkipList<int> list(arr, ARR_SIZE);

		REQUIRE_FALSE(list.Empty());
		REQUIRE_EQ(list.Size(), ARR_SIZE);

		for (std::size_t index{ 0 }; index < ARR_SIZE; ++index) {
			REQUIRE_EQ(list.At(index), index + 1);
		}

		delete[] arr;
	}

	SUBCASE("The SkipList should copy the other SkipList") {
		constexpr std::size_t ARR_SIZE{ 5 };
		int* arr{ new int[ARR_SIZE] { 1, 2, 3, 4, 5 } };

		SkipList<int> list(arr, ARR_SIZE);
		SkipList<int> copyList(list);

		REQUIRE_FALSE(copyList.Empty());
		REQUIRE_EQ(list.Size(), copyList.Size());

		for (std::size_t index{ 0 }; index < list.Size(); ++index) {
			REQUIRE_EQ(list.At(index), copyList.At(index));
		}

		delete[] arr;
	}

	SkipList<int> list;

	SUBCASE("The SkipList should PushBack elements") {
		const std::size_t ELEMS{ 5 };

		for (std::size_t elem{ 1 }; elem <= ELEMS; ++elem) {
			list.PushBack(elem);
		}

		REQUIRE_FALSE(list.Empty());
		REQUIRE_EQ(list.Size(), ELEMS);

		int val = 1;

		for (int elem : list) {
			REQUIRE_EQ(elem, val++);
		}
	}

	SUBCASE("The SkipList should PushFront elements") {
		const std::size_t ELEMS{ 5 };

		for (std::size_t elem{ 1 }; elem <= ELEMS; ++elem) {
			list.PushFront(elem);
		}

		REQUIRE_FALSE(list.Empty());
		REQUIRE_EQ(list.Size(), ELEMS);

		int val = ELEMS;

		for (int elem : list) {
			REQUIRE_EQ(elem, val--);
		}
	}

	SUBCASE("The SkipList should PopBack elements") {
		const std::size_t ELEMS{ 5 };

		for (std::size_t elem{ 1 }; elem <= ELEMS; ++elem) {
			list.PushBack(elem);
		}

		for (std::size_t index{ 1 }; index < ELEMS; ++index) {
			list.PopBack();

			REQUIRE_FALSE(list.Empty());
			REQUIRE_EQ(list.Size(), ELEMS - index);
			REQUIRE_EQ(list.At(list.Size() - 1), ELEMS - index);
		}

		list.PopBack();

		REQUIRE(list.Empty());
		REQUIRE_EQ(list.Size(), 0);
		REQUIRE_THROWS(list.PopBack());
	}

	SUBCASE("The SkipList should PopFront elements") {
		const std::size_t ELEMS{ 5 };

		for (std::size_t elem{ 1 }; elem <= ELEMS; ++elem) {
			list.PushBack(elem);
		}

		for (std::size_t index{ 1 }; index < ELEMS; ++index) {
			list.PopFront();

			REQUIRE_FALSE(list.Empty());
			REQUIRE_EQ(list.Size(), ELEMS - index);
			REQUIRE_EQ(list.At(0), index + 1);
		}

		list.PopBack();

		REQUIRE(list.Empty());
		REQUIRE_EQ(list.Size(), 0);
		REQUIRE_THROWS(list.PopBack());
	}

	SUBCASE("The SkipList should insert") {
		REQUIRE_THROWS(list.Insert(1, 2));

		list.Insert(1, 0);

		REQUIRE_FALSE(list.Empty());
		REQUIRE_EQ(list.Size(), 1);
		REQUIRE_EQ(list.At(0), 1);

		REQUIRE_THROWS(list.Insert(2, 2));

		list.Insert(2, 1);

		REQUIRE_EQ(list.Size(), 2);
		REQUIRE_EQ(list.At(0), 1);
		REQUIRE_EQ(list.At(1), 2);

		list.Insert(3, 1);

		REQUIRE_EQ(list.Size(), 3);
		REQUIRE_EQ(list.At(0), 1);
		REQUIRE_EQ(list.At(1), 3);
		REQUIRE_EQ(list.At(2), 2);

		list.Insert(4, 0);

		REQUIRE_EQ(list.Size(), 4);
		REQUIRE_EQ(list.At(0), 4);
		REQUIRE_EQ(list.At(1), 1);
		REQUIRE_EQ(list.At(2), 3);
		REQUIRE_EQ(list.At(3), 2);


		list.Insert(5, 2);

		REQUIRE_EQ(list.Size(), 5);
		REQUIRE_EQ(list.At(0), 4);
		REQUIRE_EQ(list.At(1), 1);
		REQUIRE_EQ(list.At(2), 5);
		REQUIRE_EQ(list.At(3), 3);
		REQUIRE_EQ(list.At(4), 2);
	}

	SUBCASE("The SkipList should erase") {
		constexpr std::size_t ARR_SIZE{ 5 };
		int* arr = new int[5] { 1, 2, 3, 4, 5 };
		
		SkipList<int> arrList(arr, ARR_SIZE);

		REQUIRE_THROWS(arrList.Erase(ARR_SIZE));

		arrList.Erase(2); // 1 2 4 5

		REQUIRE_EQ(arrList.Size(), 4);
		REQUIRE_EQ(arrList.At(2), 4);

		arrList.Erase(0); // 2 4 5
		REQUIRE_EQ(arrList.Size(), 3);
		REQUIRE_EQ(arrList.At(0), 2);

		arrList.Erase(arrList.Size() - 1); // 2 4
		REQUIRE_EQ(arrList.Size(), 2);
		REQUIRE_EQ(arrList.At(arrList.Size() - 1), 4);
		
		arrList.Erase(0);
		arrList.Erase(0);

		REQUIRE(arrList.Empty());

		REQUIRE_THROWS(arrList.Erase(0));
	}

	SUBCASE("The SkipList Iterators should go over every element") {
		constexpr std::size_t ARR_SIZE{ 5 };
		int* arr = new int[5] { 1, 2, 3, 4, 5 };

		list = SkipList<int>(arr, ARR_SIZE);

		Iterator<int> iter{ list.begin() };
		std::size_t index{ 0 };

		while (iter != list.end()) {
			REQUIRE_EQ(iter->m_data, arr[index++]);

			++iter;
		}
	}
}
