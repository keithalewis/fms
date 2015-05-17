// reverse.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// reverse enumerator
	template<class T>
	class reverse_enumerator : public enumerator_base<T*,T> {
		std::reverse_iterator<T*> i;
	public:
		typedef std::false_type is_counted; // for tag dispatch
		reverse_enumerator()
		{ }
		reverse_enumerator(T* i)
			: i(i) // just like reverse iterators
		{ }

		bool operator==(const reverse_enumerator& j) const
		{
			return i == j.i;
		}
		bool operator!=(const reverse_enumerator& j) const
		{
			return i != j.i;
		}
		operator T*() const
		{
			return i;
		}
		std::reverse_iterator<T*>& iterator()
		{
			return i;
		}

		operator bool() const
		{
			return true;
		}

		T operator*() const
		{
			return *i;
		}
		reverse_enumerator& operator++()
		{
			++i;

			return *this;
		}
		reverse_enumerator operator++(int)
		{
			reverse_enumerator r(*this);

			operator++();

			return r;
		}
	};
	template<class T>
	inline reverse_enumerator<T> make_renumerator(T* i)
	{
		return reverse_enumerator<T>(i);
	}
	template<class T>
	inline reverse_enumerator<T> re(T* i)
	{
		return reverse_enumerator<T>(i);
	}

} // iter


#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_reverse()
{
	int a[] = {1,2,3};
	auto ra = re(a + 3);
	ensure (*ra == 3);
	ensure (*++ra == 2);
	ra++;
	ensure (*ra == 1);
}

#endif // _DEBUG