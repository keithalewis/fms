// level.h - pairs with a constant sum
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {
	
	// (0,n), (1,n-1), ...(n, 0)
	template<class T>
	class level_ : public enumerator<void,std::pair<T,T>,std::input_iterator_tag> {
		T i, n;
	public:
		level_()
		{ }
		level_(T n)
			: i(0), n(n)
		{ }

		size_t size() const
		{
			return n - i;
		}

		operator bool() const
		{
			return i <= n;
		}
		std::pair<T,T> operator*() const
		{
			return std::make_pair(i, n - i);
		}
		level_& operator++()
		{
			++i;

			return *this;
		}
		level_ operator++(int)
		{
			level_ l(*this);

			operator++();

			return l;
		}
	};
	template<class T>
	inline auto level(T n)
	{
		return level_<T>(n);
	}
} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_level()
{
	auto l = level(3);
	ensure (*l == std::make_pair(0,3));
	ensure (*++l == std::make_pair(1,2));
	l++;
	ensure (*l == std::make_pair(2,1));
	ensure (*++l == std::make_pair(3,0));
	ensure (!++l);
}

#endif // _DEBUG