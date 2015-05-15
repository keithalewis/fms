// null.h - null terminated enumerators
#pragma once
#include "../enumerator.h"

namespace iter {

	// null terminated enumerator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class null_enumerator : public enumerator<I,T> {
	public:
		using enumerator<I,T>::enumerator;
		using enumerator<I,T>::i;

		operator bool() const
		{
			return *i != 0;
		}
		T operator*() const
		{
			return *i;
		}
		null_enumerator& operator++()
		{
			++i;

			return *this;
		}
		null_enumerator operator++(int)
		{
			null_enumerator e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline null_enumerator<I,T> make_null_enumerator(I i)
	{
		return null_enumerator<I,T>(i);
	}
	// shorthand
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline null_enumerator<I,T> e(I i)
	{
		return null_enumerator<I,T>(i);
	}

	// specialize for std::is_floating_point???
	// specialize for doubles
	template<class I>
	class null_enumerator<I,double> : public enumerator_base<I,double> {
		I i;
	public:
		null_enumerator()
		{ }
		null_enumerator(I i)
			: i(i)
		{ }

		operator bool() const
		{
			return std::isnormal(*i) && *i != 0;
		}
		double operator*() const
		{
			return *i;
		}
		null_enumerator& operator++()
		{
			++i;

			return *this;
		}
		null_enumerator operator++(int)
		{
			null_enumerator e(*this);

			operator++();

			return e;
		}
	};
	// specialize for floats
	template<class I>
	class null_enumerator<I,float> : public enumerator_base<I,float> {
		I i;
	public:
		null_enumerator()
		{ }
		null_enumerator(I i)
			: i(i)
		{ }

		operator bool() const
		{
			return std::isnormal(*i) && *i != 0;
		}
		float operator*() const
		{
			return *i;
		}
		null_enumerator& operator++()
		{
			++i;

			return *this;
		}
		null_enumerator operator++(int)
		{
			null_enumerator e(*this);

			operator++();

			return e;
		}
	};


} // iter


#ifdef _DEBUG
#include <cassert>
#include <vector>

using namespace iter;

inline void test_enumerator_null()
{
	{
		auto b = make_null_enumerator("foo");
		auto e(b);
		while (e)
			++e;
//!!!		assert (3 == std::distance(b, e));
		}
}

#endif // _DEBUG