// fmap.h - enumerator of enumerators
#pragma once
#include "enumerator.h"

namespace iter {

	// f(i[0]), f(i[1]), ...
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class fmap_ : public enumerator<I,U,C> {
		F f;
	public:
		using enumerator<I,U,C>::i;
		typedef typename enumerator_traits<I>::is_counted is_counted;

		fmap_()
		{ }
		fmap_(F f, I i)
			: enumerator<I,U,C>(i), f(f)
		{ }

		operator bool() const
		{
			return i;
		}
		U operator*()
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
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto fmap(F f, I i)
	{
		return fmap_<F,I,T,U,C>(f, i);
	}

	// {e0, e1, ...} => {e0[0], e0[1], ..., e1[0], e1[1], ...
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	class flatten_ : public enumerator<I,T,std::input_iterator_tag> {
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
		using enumerator<I,T,std::input_iterator_tag>::i;
		typedef typename enumerator_traits<I>::is_counted is_counted;

		flatten_()
		{ }
		flatten_(I i)
			: enumerator<I,T,std::input_iterator_tag>(i), _i(*i)
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
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto flatten(I i)
	{
		return flatten_<I,typename T::value_type>(i);
	}
	// bind
	// return

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "constant.h"

inline void test_fmap()
{
	{
		int a[] = {0,1,2};
	
		// {{0,1,2},{1,2},{2}}
		auto aa = fmap([&](int i) { return ce(a+i, 3-i); }, a);
		auto b = *aa;
		ensure (*b == 0);
		ensure (*++b == 1);
		b++;
		ensure (*b == 2);

		b = *++aa;
		ensure (*b == 1);
		++b;
		ensure (*b == 2);

		aa++;
		b = *aa;
		ensure (*b == 2);
		ensure (!++b);

		auto dd = fmap([&](int i) { return ce(a+i, 3-i); }, a);
		auto c = flatten(dd);
		ensure (*c == 0);
		++c;
		ensure (*c == 1);
		++c;
		ensure (*c == 2);
		++c;
		ensure (*c == 1);
		++c;
		ensure (*c == 2);
		++c;
		ensure (*c == 2);
	}
	{
		int a[] = {1,0,2,0,0,3};
		auto aa = fmap([&](int i) { return ce(c(i),i); }, a);
		auto _a = flatten(aa);
		ensure (*_a == 1);
		++_a;
		ensure (*_a == 2);
		++_a;
		ensure (*_a == 2);
		++_a;
		ensure (*_a == 3);
		++_a;
		ensure (*_a == 3);
		++_a;
		ensure (*_a == 3);
	}
}

#endif // _DEBUG