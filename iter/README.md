﻿# enumerators - iterators that know when they are done

An `enumerator` is an iterator that provides `operator bool() const`
which returns `true` when it is valid to dereference the iterator.
This is similar to `MoveNext` in the `IEnumerator` C# interface,
but fits in better with C++ notions of iteration.
If the iterator has an end it behaves like `i != end`.

The basic idea is that `enumerator<I,T>` is an iterator
that uses `I` for iteration and returns value_type `T`,
perhaps different from `I::value_type`.
The canonical example is applying a function from T → U on an input iterator.
The resulting iterator should be of type `enumerator<I,U>`.

All classes deriving from `enumerator` are  simple: drag in the
iterator with `using enumerator::i` then add
the necessary accoutrements in the constructor and implement
`operator bool() const`, `operator*`, and `operator++` pre and post increment. 
These hide the implementation in the base class instead of overriding, but enumerator
algorithms pass everything by value so the correct implementation
will be supplied at compile time and hopefully be optimized.

The convention is to use `class_` for class names and `class` instead of `make_class`. 
Users never need to use `class_` directly, just the corresponding template function.

The purpose is to make C++ more expressive for implementing numerical algorithms. The
bias is to assume all iterators are input iterators over unaliased data. The inspiration
comes from Fortran and APL, but incorporates recent functional programming notions.

For example, here is the implementation of Horner's method:
```cpp
	// c[0] + x*(c[1] + ... + x(c[n-2] + x*c[n-1])...)
	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X horner(C c, const X& x)
	{
		return back(scan([x](const X& a, const X& b) { return x*a + b; }, rend(c), X(0)));
	}
```

This computes `exp(x)` to machine precision:
```cpp
	// exp(x) = sum_0 x^n/n!
	template<class X>
	inline X exp(const X& x)
	{
		return X(1 + sum0(ne(prod(c(x)/iota(X(1))))));
	}
```
`c(x)` is the constant enumerator that always returns `x`. `iota(1)` returns 1, 2, 3, ...
`prod` yields `x/1`, `x^2/1*2`, `x^3/1*2*3`... `ne` returns a null enumerator that terminates
when `x^n/n!` is zero to machine epsilon. `sum0` adds up the finite number
of terms produced by the null enumerator. The first term in the sum is a special case.

## TODO

Get unary operator+ working with MSVC. Ambiguous return types based on calling convention.

operator, => concatenate

operator^ => monotonic cycle

Fix where.