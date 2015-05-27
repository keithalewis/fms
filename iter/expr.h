// expr.h - iter expressions
#pragma once
#include <functional>
#include "pair.h"

namespace iter {

	template<class O, class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	class binop_ : public enumerator_<std::pair<I,J>,V,C> {
		O o;
	public:
		using enumerator_<std::pair<I,J>,V,C>::i;

		binop_()
		{ }
		binop_(O o, I i, J j)
			: enumerator_<std::pair<I,J>,V,C>(std::make_pair(i, j)), o(o)
		{ }

		explicit operator bool() const
		{
			return i.first && i.second;
		}
		V operator*() const
		{
			return o(*i.first, *i.second);
		}
		binop_& operator++()
		{
			++i.first;
			++i.second;

			return *this;
		}
		binop_ operator++(int)
		{
			binop_ a(*this);

			operator++();

			return a;
		}
	};
	template<class O, class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto binop(O o, I i, J j)
	{
		return binop_<O,I,J,T,U,V,C>(o, i, j);
	}

} // iter

template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type,
	class V = typename std::common_type_t<T,U>,
	class C = typename std::common_type_t<
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<J>::iterator_category
	>
>
inline auto operator+(I i, J j)
{
	return iter::binop_<std::plus<V>,I,J,T,U,V,C>(std::plus<V>{}, i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type,
	class V = typename std::common_type_t<T,U>,
	class C = typename std::common_type_t<
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<J>::iterator_category
	>
>
inline auto operator-(I i, J j)
{
	return iter::binop_<std::minus<V>,I,J,T,U,V,C>(std::minus<V>{}, i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type,
	class V = typename std::common_type_t<T,U>,
	class C = typename std::common_type_t<
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<J>::iterator_category
	>
>
inline auto operator*(I i, J j)
{
	return iter::binop_<std::multiplies<V>,I,J,T,U,V,C>(std::multiplies<V>{}, i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type,
	class V = typename std::common_type_t<T,U>,
	class C = typename std::common_type_t<
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<J>::iterator_category
	>
>
inline auto operator/(I i, J j)
{
	return iter::binop_<std::divides<V>,I,J,T,U,V,C>(std::divides<V>{}, i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type,
	class V = typename std::common_type_t<T,U>,
	class C = typename std::common_type_t<
		typename std::iterator_traits<I>::iterator_category,
		typename std::iterator_traits<J>::iterator_category
	>
>
inline auto operator%(I i, J j)
{
	return iter::binop_<std::modulus<V>,I,J,T,U,V,C>(std::modulus<V>{}, i, j);
}

namespace iter {

	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto equal_to(I i, J j)
	{
		return iter::binop_<std::equal_to<V>,I,J,T,U,bool,C>(std::equal_to<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto not_equal_to(I i, J j)
	{
		return iter::binop_<std::not_equal_to<V>,I,J,T,U,bool,C>(std::not_equal_to<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto less(I i, J j)
	{
		return iter::binop_<std::less<V>,I,J,T,U,bool,C>(std::less<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto less_equal(I i, J j)
	{
		return iter::binop_<std::less_equal<V>,I,J,T,U,bool,C>(std::less_equal<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto greater(I i, J j)
	{
		return iter::binop_<std::greater<V>,I,J,T,U,bool,C>(std::greater<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto greater_equal(I i, J j)
	{
		return iter::binop_<std::greater_equal<V>,I,J,T,U,bool,C>(std::greater_equal<V>{}, i, j);
	}

	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto logical_and(I i, J j)
	{
		return iter::binop_<std::logical_and<V>,I,J,T,U,bool,C>(std::logical_and<V>{}, i, j);
	}
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type,
		class V = typename std::common_type_t<T,U>,
		class C = typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category
		>
	>
	inline auto logical_or(I i, J j)
	{
		return iter::binop_<std::logical_or<V>,I,J,T,U,bool,C>(std::logical_or<V>{}, i, j);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "constant.h"

using namespace iter;

template<class T, class U, template<typename TU> class O>
inline void test_expr_binop()
{
	O<std::common_type_t<T,U>> o{};
	T a[] = {1,2,3};
	U b[] = {4,5,6};

	auto ab = binop(o, a, b);
	int i = 0;
	ensure (*ab == o(a[i],b[i]));
	ab++; i++;
	ensure (*ab == o(a[i],b[i]));
	++i;
	ensure (*++ab == o(a[i],b[i]));
}

inline void test_expr()
{
	test_expr_binop<int,int,std::plus>();
	test_expr_binop<int,double,std::plus>();
	test_expr_binop<double,int,std::plus>();
	test_expr_binop<double,double,std::plus>();

	test_expr_binop<int,int,std::minus>();
	test_expr_binop<int,double,std::minus>();
	test_expr_binop<double,int,std::minus>();
	test_expr_binop<double,double,std::minus>();

	test_expr_binop<int,int,std::multiplies>();
	test_expr_binop<int,double,std::multiplies>();
	test_expr_binop<double,int,std::multiplies>();
	test_expr_binop<double,double,std::multiplies>();

	test_expr_binop<int,int,std::divides>();
	test_expr_binop<int,double,std::divides>();
	test_expr_binop<double,int,std::divides>();
	test_expr_binop<double,double,std::divides>();

	int a[] = {1,2,3};
	{
		auto aa = e(a) + e(a);
		auto bb(aa);
		aa = bb;
		ensure (*aa == 1 + 1);
		ensure (*++aa == 2 + 2);
		aa++;
		ensure (*aa == 3 + 3);

		auto aaa = e(a) + e(a) + e(a);
		ensure (*aaa == 3);
		ensure (*++aaa == 6);
		aaa++;
		ensure (*aaa == 9);

		aa = e(a) + e(a);
		auto a4 = aa + e(a);
		ensure (*a4 == 3);
		ensure (*++a4 == 6);
		a4++;
		ensure (*a4 == 9);

		auto ai = e(a);
		auto a5 = (ai + ai) + (ai + ai) + ai;
		int i = 0;
		ensure (*a5 == 5*a[i]);
		ensure (*++a5 == 5*a[++i]);
		a5++;
		ensure (*a5 == 5*a[++i]);
		{
			auto a6 = e(a) + c(1);// constant<int>(1);
			ensure (*a6 == a[i=0] + 1);
			ensure (*++a6 == a[++i] + 1);
			a6++; i++;
			ensure (*a6 == a[i] + 1);
		}
		{
			auto a6 = constant<int>(1) + e(a);
			ensure (*a6 == a[i=0] + 1);
			ensure (*++a6 == a[++i] + 1);
			a6++; i++;
			ensure (*a6 == a[i] + 1);
		}

	}
	{
		auto aa = e(a) * e(a);
		ensure (*aa == 1 * 1);
		ensure (*++aa == 2 * 2);
		aa++;
		ensure (*aa == 3 * 3);

		aa = e(a) * e(a);
		auto a4 = aa * e(a);
		ensure (*a4 == 1);
		ensure (*++a4 == 8);
		a4++;
		ensure (*a4 == 27);
	}
	{
		int a[] = {1,2,3};
		auto b = equal_to(a,a);
		ensure (*b);
		ensure (*b++ && *b++ && *b++);

		auto c = equal_to(a, e(std::reverse_iterator<int*>(a + 3)));
		ensure (!*c);
		ensure (*++c);
		c++;
		ensure (!*c);
		ensure (c && ++c);
	}

}
#endif // _DEBUG
