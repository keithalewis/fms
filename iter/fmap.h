// fmap.h - enumerator of enumerators
#pragma once
#include "enumerator.h"

namespace iter {

	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	class fmap_ : public enumerator_base<I, std::result_of_t<F(T)>> {
		F f;
		I i;
	public:
		fmap_()
		{ }
		fmap_(F f, I i)
			: f(f), i(i)
		{ }

		operator bool() const
		{
			return i;
		}
		std::result_of_t<F(T)> operator*()
		{
			return f(*i);
		}
		fmap_& operator++()
		{
			++i;

			return *this;
		}
		fmap_ operator++(int)
		{
			fmap_ f_(*this);

			operator++();

			return f_;
		}
	};
	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto fmap(F f, I i)
	{
		return fmap_<F,I,T>(f, i);
	}

	// {e0, e1, ...} => {e0[0], e0[1], ..., e1[0], e1[1], ...
	template<class I, class T = typename std::iterator_traits<I>::value_type::value_type>
	class flatten_ : public enumerator_base<I,T> {
		I i; // iterator of iterators
		typename std::iterator_traits<I>::value_type _i;
		// skip empty iterators
		void elide()
		{
			while (i && !_i) {
				++i;
				_i = *i;
			}
		}
	public:
		flatten_()
		{ }
		flatten_(I i)
			: i(i), _i(*i)
		{
			elide();
		}

		operator bool() const
		{
			return i;
		}
		T operator*() const
		{
			return *_i;
		}
		flatten_& operator++()
		{
			if (i) {
				if (_i)
					++_i;
				if (!_i) {
					++i;
					_i = *i;
				}
				elide();
			}

			return *this;
		}
		flatten_ operator++(int)
		{
			flatten_ f(*this);

			operator++();

			return f;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type::value_type>
	inline auto flatten(I i)
	{
		return flatten_<I,T>(i);
	}
	// bind
	// return

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_fmap()
{
	{
		int a[] = {0,1,2};
	
		// {{0,1,2},{1,2},{2}}
		auto aa = fmap([&](int i) { return e(a+i, 3-i); }, a);
		auto b = *aa;
		assert (*b == 0);
		assert (*++b == 1);
		b++;
		assert (*b == 2);

		b = *++aa;
		assert (*b == 1);
		++b;
		assert (*b == 2);

		aa++;
		b = *aa;
		assert (*b == 2);
		assert (!++b);

		auto dd = fmap([&](int i) { return e(a+i, 3-i); }, a);
		auto c = flatten(dd);
		assert (*c == 0);
		++c;
		assert (*c == 1);
		++c;
		assert (*c == 2);
		++c;
		assert (*c == 1);
		++c;
		assert (*c == 2);
		++c;
		assert (*c == 2);
	}
	{
		int a[] = {1,0,2,0,0,3};
		auto aa = fmap([&](int i) { return e(c(i),i); }, a);
		auto _a = flatten(aa);
		assert (*_a == 1);
		++_a;
		assert (*_a == 2);
		++_a;
		assert (*_a == 2);
		++_a;
		assert (*_a == 3);
		++_a;
		assert (*_a == 3);
		++_a;
		assert (*_a == 3);
	}
}

#endif // _DEBUG