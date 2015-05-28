// null.h - null terminated enumerators
#pragma once
#include <cmath>
#include <limits>
#include <numeric>
#include "../enumerator.h"

namespace iter {

	namespace detail {
		template<class T>
		inline bool operator_bool(const T& t)
		{
			return t != 0;
		}
		template<>
		inline bool operator_bool<double>(const double& t)
		{
			return std::isnormal(t) && t + 1 != 1;
		}
		template<>
		inline bool operator_bool<float>(const float& t)
		{
			return std::isnormal(t) && t + 1.f != 1.f;
		}
	}

	// null terminated enumerator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class null_enumerator_ : public enumerator_<I,T> {
	public:
		using enumerator_<I,T>::i;

		null_enumerator_()
		{ }
		null_enumerator_(I i)
			: enumerator_<I,T>(i)
		{ }

		explicit operator bool() const
		{
			return detail::operator_bool<T>(operator*());
		}
		T operator*() const
		{
			return *i;
		}
		null_enumerator_& operator++()
		{
			++i;

			return *this;
		}
		null_enumerator_ operator++(int)
		{
			null_enumerator_ n(*this);

			operator++();

			return n;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto null_enumerator(I i)
	{
		return null_enumerator_<I,T>(i);
	}
	// shorthand
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto ne(I i)
	{
		return null_enumerator(i);
	}

} // iter


#ifdef _DEBUG
#include "include/ensure.h"
#include <vector>

using namespace iter;

inline void test_enumerator_null()
{
	{
		auto b = null_enumerator("foo");
		auto e(b);
		while (e)
			++e;
		ensure (3 == std::distance(b, e));
		ensure (3 == e - b);
	}
	{
		double a[] = {1,2,0};
		auto b = ne(a);
		ensure (*b++ == 1 && *b++ == 2 && !b);
	}
	{
		double a[] = {1,2,std::numeric_limits<double>::infinity()};
		auto b = ne(a);
		ensure (*b++ == 1 && *b++ == 2 && !b);
	}
	{
		double a[] = {1,2,std::numeric_limits<double>::quiet_NaN()};
		auto b = ne(a);
		ensure (*b++ == 1 && *b++ == 2 && !b);
	}
	{
		double a[] = {1,2,std::numeric_limits<double>::epsilon()/2};
		auto b = ne(a);
		ensure (*b++ == 1 && *b++ == 2);
		ensure (std::numeric_limits<double>::epsilon()/2 != 0);
		ensure (1 + std::numeric_limits<double>::epsilon()/2 == 1);
		ensure (!b);
	}
}

#endif // _DEBUG