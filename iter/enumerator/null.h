// null.h - null terminated enumerators
#pragma once
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
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class null_enumerator : public enumerator<I,T,C> {
	public:
		using enumerator<I,T,C>::i;

		typedef std::false_type is_counted; // for tag dispatch
		null_enumerator()
		{ }
		null_enumerator(I i)
			: enumerator<I,T,C>(i)
		{ }

		operator bool() const
		{
			return detail::operator_bool<T>(operator*());
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
	inline null_enumerator<I,T> ne(I i)
	{
		return null_enumerator<I,T>(i);
	}

} // iter


#ifdef _DEBUG
#include "include/ensure.h"
#include <vector>

using namespace iter;

inline void test_enumerator_null()
{
	{
		auto b = make_null_enumerator("foo");
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