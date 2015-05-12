// sequence.h - sequence of numbers
#pragma once
#include <limits>
#include "enumerator.h"

namespace iter {

	template<class T>
	class sequence : public enumerator<const T*,T> {
		T i, start, step, stop;
	public:
		sequence(const T& start = 0, const T& step = 1, const T& stop = std::numeric_limits<T>::max())
			: i(start), start(start), step(step), stop(stop)
		{ }
		sequence(const sequence&) = default;
		sequence(sequence&&) = default;
		sequence& operator=(const sequence&) = default;
		sequence& operator=(sequence&&) = default;
		~sequence()
		{ }

		operator bool() const
		{
			return i <= stop;
		}
		bool operator!=(const sequence& s) const
		{
			return i != s.i || start != s.start || step != s.step || stop != s.stop;
		}
		T operator*() const
		{
			if (!operator bool())
				throw std::out_of_range("iter::sequence::operator*(): out of range");

			return i;
		}
		sequence& operator++()
		{
			i += step;

			return *this;
		}
		sequence operator++(int)
		{
			sequence s(*this);

			operator++();

			return s;
		}
	};
	template<class T>
	inline sequence<T> make_sequence(const T& b = 0, const T& s = 1, const T& e = std::numeric_limits<T>::max())
	{
		return sequence<T>(b, s, e);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_sequence()
{
	sequence<int> s;
	assert (s);
	assert (*s == 0);
	assert (*++s == 1);
	s++;
	assert (*s == 2);

	auto t = make_sequence(1);
	assert (t);
	assert (*t == 1);
	assert (*++t == 2);
	t++;
	assert (*t == 3);

	auto u = make_sequence(2,3);
	assert (u);
	assert (*u == 2);
	assert (*++u == 5);
	u++;
	assert (*u == 8);
	
	auto v = make_sequence(4,5,6);
	assert (v);
	assert (*v++ == 4);
	/*
	bool thrown = false;
	try {
		int i = *v;
	}
	catch (const std::exception&) {
		thrown = true;
	}
	assert (thrown);
	*/

	assert (!v);

	auto w = make_sequence(-2, 2, 2);
	assert (*w++ == -2 && *w++ == 0 && *w++ == 2);
	assert (!w);
}

#endif // _DEBUG