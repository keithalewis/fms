// concatenate.h - concatenate an enumerator and an iterator
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {

	template<class I, class J,
		class V = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>
	>
	class concatenate_ : public enumerator_<std::pair<I,J>,V,std::input_iterator_tag> {
	public:
		using enumerator_<std::pair<I,J>,V,std::input_iterator_tag>::i;

		concatenate_()
		{ }
		concatenate_(I i_, J j)
//			: enumerator_<std::pair<I,J>,V,std::input_iterator_tag>(std::make_pair(i,j))
		{
			i.first = i_;
			i.second = j;
		}
		// why not compiler generated???
		concatenate_(const concatenate_& c)
//			: enumerator_<std::pair<I,J>,V,std::input_iterator_tag>(c.i)
		{
			i.first = c.i.first;
			i.second = c.i.second;
		}

		explicit operator bool() const
		{
			return i.first || i.second;
		}
		V operator*() const
		{
			return i.first ? *i.first : *i.second;
		}
		concatenate_& operator++()
		{
			if (i.first)
				++i.first;
			else
				++i.second;

			return *this;
		}
		concatenate_ operator++(int)
		{
			concatenate_ k(*this);

			operator++();

			return k;
		}
	};
	template<class I, class J,
		class V = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>
	>
	inline auto concatenate(I i, J j)
	{
		return concatenate_<I,J,V>(i, j);
	}
	template<class I>
	inline auto cat(I i)
	{
		return i;
	}
	template<class I, class... Is>
	inline auto cat(I i, Is... is)
	{
		return concatenate(i, cat(is...));
	}

} // iter



#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"
#include "enumerator/null.h"
//#include "fmap.h"
#include "unit.h"
#include "util.h"

using namespace iter;

inline void test_concatenate()
{
	int i[] = {1,2,0};
	int j[] = {3,4};

	{
/*		auto c = concatenate(ne(i), ce(j, 2));
		auto d(c);
		c = d;
		ensure (*d == *c);
		ensure (*c == 1);
		ensure (*++c == 2);
		ensure (*++c == 3);
		c++;
		ensure (*c == 4);
*/	}
	{
		auto c = concatenate(ne(i), ce(j, 2));
		ensure (*c == 1);
		ensure (*++c == 2);
		ensure (*++c == 3);
		c++;
		ensure (*c == 4);
	}
	{
		auto a = ce(iota(0),2);
		auto aa = cat(a,a);
		ensure(*aa++ == 0 && *aa++ == 1);
		ensure(*aa++ == 0 && *aa++ == 1);
		auto aaa = cat(a,a,a);
		ensure(*aaa++ == 0 && *aaa++ == 1);
		ensure(*aaa++ == 0 && *aaa++ == 1);

		auto d = ce(iota<double>(0), 2);
		auto ad = cat(a,d);
		ensure(*ad++ == 0 && *ad++ == 1);
		ensure(*ad++ == 0 && *ad++ == 1);
	}
	{
/*		auto c = operator,(ne(i),ce(j,2));
		auto c = ne(i),e(j);
		ensure (*c == 1);
		ensure (*++c == 2);
		ensure (*++c == 3);
		c++;
		ensure (*c == 4);
*/	}
	{
		int a[] = {1,2};
		auto b = cat(ce(a),ce(a),ce(a));
		ensure (*b++ == 1);
		ensure (*b++ == 2);
		ensure (*b++ == 1);
		ensure (*b++ == 2);
		ensure (*b++ == 1);
		ensure (*b++ == 2);
		ensure (!b);
	}
/*	{	// cartesian product
//		auto a = ce(iota(1),2); // {1,2}
		auto b = ce(iota(0),3); // {0,1,2}
		// {{1,0}, {1,1}, {1,2}
		//  {2,0}, {2,1}, {2,2}}
		auto x = fmap(N_(cat(unit(1),unit(n))), b);
		auto y = *x;
		ensure (*y == 1 && *++y == 0);
		y = *++x;
		ensure (*y == 1 && *++y == 1);
		y = *++x;
		ensure (*y == 1 && *++y == 2);
	}
*/
}

#endif // _DEBUG