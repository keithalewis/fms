// range_sequence.h - linear sequence of values
#pragma once
#include <limits>
#include "range.h"


namespace range {

	// [ start, start + step, ..., stop )
	template<class T>
	class sequence : public enumerator<T*> {
		T start, step, stop;
		T t;
	public:
		sequence(T start = T(0), T step = T(1), T stop = std::numeric_limits<T>::max())
			: start(start), step(step), stop(stop), t(start)
		{ }
		sequence(const sequence&) = default;
		sequence& operator=(const sequence&) = default;
		~sequence()
		{ }

		operator bool() const override
		{
			return t < stop;
		}
		bool operator==(const sequence& i) const
		{
			return t == i.t
				&& start == i.start
				&& step == i.step
				&& stop == i.stop;
		}
		T operator*() const 
		{
			return t;
		}
		sequence& operator++()
		{
			t += step;

			return *this;
		}
		sequence operator++(int)
		{
			sequence i(*this);

			operator++();

			return i;
		}
	};
	template<class T>
	inline sequence<T> make_sequence(T start = T(0), T step = T(1), 
			T stop = std::numeric_limits<T>::max())
	{
		return sequence<T>(start, step, stop);
	}
#ifdef _DEBUG

	inline void test_sequence()
	{
		{
			sequence<int> s;
			assert (s);
			assert (*s == 0);
			assert (s);
			assert (*++s == 1);
			assert (s);
			assert (*s++ == 1);
			assert (s);
			assert (*s == 2);
		}
		{
			sequence<int> s(0,1,3);
			assert (s);
			assert (*s == 0);
			assert (s);
			assert (*++s == 1);
			assert (s);
			assert (*s++ == 1);
			assert (s);
			assert (*s == 2);
			++s;
			assert (!s);
		}
		{
			sequence<int> s(0,1,3), t(3,1);
			auto st = make_concatenate(s,t);
			assert (*st == 0);
			assert (*st == 0);
		}
	}

#endif // _DEBUG
} // range
