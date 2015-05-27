// buffer.h - buffer enumerator values
#pragma once
#include <valarray>
#include "enumerator.h"

namespace iter {

	template<class I>
	class buffer_ : public I {
		typedef typename I::value_type T;
		
		int n;
		std::valarray<T> t;
	public:
		buffer_()
			: n(0), t(0)
		{ }
		buffer_(I i, int n = 0)
			: I(i), n(n), t(0)
		{ }

		// pseudo size
		int size() const
		{
			return static_cast<int>(t.size());
		}

		const T& operator[](int n)
		{
			return t[n + (n < 0 ? size() : 0)];
		}
		explicit operator bool() const
		{
			return I::operator bool();
		}
		T operator*() const
		{
			return I::operator*();
		}
		buffer_& operator++()
		{
			if (n == 0 || (n > 0 && size() < n)) {
				std::valarray<T> t_(size() + 1);
				if (size() != 0)
					t_[std::slice(0, size(), 1)] = t;
				t_[size()] = I::operator*();
				t_.swap(t);
			}
			else if (n == -1 || (n < -1 && size() < -n)) {
				std::valarray<T> t_(size() + 1);
				if (size() != 0)
					t_[std::slice(1, size() + 1, 1)] = t;
				t_[0] = I::operator*();
				t_.swap(t);
			}
			else if (n > 0 && size() >= n) {
				t = t.shift(1);
				t[size() - 1] = I::operator*();
			}
			else { // n < -1 && size() >= -n
				t = t.shift(-1);
				t[0] = I::operator*();
			}

			I::operator++();

			return *this;
		}
		buffer_ operator++(int)
		{
			buffer_ b(*this);

			operator++();

			return b;
		}
	};

	template<class I/*, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category*/
	>
	inline auto buffer(int n, I i)
	{
		return buffer_<I>(i, n);
	}


} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "iota.h"

using namespace iter;

inline void test_buffer()
{
	{
		auto i = iota(0);
		auto b = buffer(0, i);
		ensure (*b == 0);

		++b;
		ensure (*b == 1);
		ensure (b.size() == 1);
		ensure (b[0] == 0);
		ensure (b[-1] == 0);

		++b;
		ensure (*b == 2);
		ensure (b.size() == 2);
		ensure (b[0] == 0);
		ensure (b[1] == 1);
		ensure (b[-1] == 1);
		ensure (b[-2] == 0);

		++b;
		ensure (*b == 3);
		ensure (b.size() == 3);
		ensure (b[0] == 0);
		ensure (b[1] == 1);
		ensure (b[2] == 2);
		ensure (b[-1] == 2);
		ensure (b[-2] == 1);
		ensure (b[-3] == 0);
	}
	{
		auto i = iota(0);
		auto b = buffer(-1, i);
		ensure (*b == 0);

		++b;
		ensure (*b == 1);
		ensure (b.size() == 1);
		ensure (b[0] == 0);
		ensure (b[-1] == 0);

		++b;
		ensure (*b == 2);
		ensure (b.size() == 2);
		ensure (b[0] == 1);
		ensure (b[1] == 0);
		ensure (b[-1] == 0);
		ensure (b[-2] == 1);
	}
	{
		auto i = iota(0);
		auto b = buffer(2, i);
		ensure (*b == 0);

		++b;
		ensure (*b == 1);
		ensure (b.size() == 1);
		ensure (b[0] == 0);
		ensure (b[-1] == 0);

		++b;
		ensure (*b == 2);
		ensure (b.size() == 2);
		ensure (b[0] == 0);
		ensure (b[1] == 1);
		ensure (b[-1] == 1);
		ensure (b[-2] == 0);

		++b;
		ensure (*b == 3);
		ensure (b.size() == 2);
		ensure (b[0] == 1);
		ensure (b[1] == 2);
	}
	{
		auto i = iota(0);
		auto b = buffer(-2, i);
		ensure (*b == 0);

		++b;
		ensure (*b == 1);
		ensure (b.size() == 1);
		ensure (b[0] == 0);
		ensure (b[-1] == 0);

		++b;
		ensure (*b == 2);
		ensure (b.size() == 2);
		ensure (b[0] == 1);
		ensure (b[1] == 0);
		ensure (b[-1] == 0);
		ensure (b[-2] == 1);

		++b;
		ensure (*b == 3);
		ensure (b.size() == 2);
		ensure (b[0] == 2);
		ensure (b[1] == 1);
	}
}

#endif // _DEBUG