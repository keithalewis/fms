// enumerator.h - input iterators having operator bool()
// Copyright (c) KALX, LLC. All rights reserved. No warranty made.

#pragma once
#include <iterator>

namespace iter {

	// iterator having explicit operator bool() const
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	struct enumerator_ : public std::iterator<std::input_iterator_tag,T> {
	protected:
		I i;
	public:
		enumerator_()
		{ }
		enumerator_(I i)
			: i(i)
		{ }

		bool operator==(const enumerator_& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator_& j) const
		{
			return i != j.i;
		}

		operator I() const
		{
			return i;
		}
		I begin() const
		{
			return i;
		}
		I end() const
		{
			return nullptr;
		}

		explicit operator bool() const
		{
			return true; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		enumerator_& operator++()
		{
			++i;

			return *this;
		}
		enumerator_ operator++(int)
		{
			enumerator_ e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto enumerator(I i)
	{
		return enumerator_<I,T>(i);
	}
	// shorthand
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto e(I i)
	{
		return enumerator<I,T>(i);
	}

	// specialize for empty iterators
	template<class T>
	struct enumerator_<void,T> : public std::iterator<std::input_iterator_tag,T> {
	};

	// specializations for pointers
	template<class T>
	class enumerator_<T*,T> : public std::iterator<std::random_access_iterator_tag,T> {
	protected:
		T* i;
	public:
		enumerator_()
		{ }
		enumerator_(T* i)
			: i(i)
		{ }

		bool operator==(const enumerator_& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator_& j) const
		{
			return i != j.i;
		}

		operator T*() const
		{
			return i;
		}
		T* begin() const
		{
			return i;
		}
		T* end() const
		{
			return nullptr;
		}

		explicit operator bool() const
		{
			return true; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		enumerator_& operator++()
		{
			++i;

			return *this;
		}
		enumerator_ operator++(int)
		{
			enumerator_ e(*this);

			operator++();

			return e;
		}
	};

	// specializations for const pointers
	template<class T>
	class enumerator_<const T*,T> : public std::iterator<std::random_access_iterator_tag,T> {
	protected:
		const T* i;
	public:
		enumerator_()
		{ }
		enumerator_(const T* i)
			: i(i)
		{ }

		bool operator==(const enumerator_& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator_& j) const
		{
			return i != j.i;
		}

		operator T*() const
		{
			return i;
		}
		T* begin() const
		{
			return i;
		}
		T* end() const
		{
			return nullptr;
		}

		explicit operator bool() const
		{
			return true; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		enumerator_& operator++()
		{
			++i;

			return *this;
		}
		enumerator_ operator++(int)
		{
			enumerator_ e(*this);

			operator++();

			return e;
		}
	};

} // iter

#ifdef _DEBUG
#include <type_traits>
#include <vector>
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator()
{

	int a[] = {1,2,3};

	{
		enumerator_<int*> b(a), c;
		c = b;
		ensure (b == c);
		ensure (*c == *b);
		ensure (b);
		ensure (*++b == 2);
		b++; // not really the end
		ensure (b != c);
	}
	{
		auto b = enumerator(a);
		auto c(b);
		b = c;
		ensure (b);
		ensure (*++b == 2);
		b++;
		using C = std::iterator_traits<decltype(b)>::iterator_category;
		static_assert(std::is_same<C,std::random_access_iterator_tag>::value,
			"supposted to all specialize operator T*() const");
		ensure (std::distance(c,b) == 2);

		int* pb = b; // calls operator T*() const
		--pb;
		ensure (*pb == 2);
	}
	{
		auto b = e(a);

		int i;
		i = 0;
		for (auto c : b) {
			ensure (c == a[i++]);
			if (i == 2)
				break;
		}
		ensure (b.end() == nullptr);
		i = 0;
		for (auto& c : b) {
			ensure (c == a[i++]);
			if (i == 2)
				break;
		}
		i = 0;
		for (const auto& c : b) {
			ensure (c == a[i++]);
			if (i == 2)
				break;
		}
	}
	{
		std::vector<int> a = {1,2,3};
		auto b = e(a.begin());
		ensure (*b == 1);
		ensure (*++b == 2);
		b++;
		ensure (*b == 3);
		b = a.begin();
		auto c = e(a.end());
		ensure (static_cast<size_t>(std::distance(b,c)) == a.size());
	}
}

#endif // _DEBUG