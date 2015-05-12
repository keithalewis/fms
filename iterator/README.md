# Iterator - input iterator and range classes for numerical computation

This project solves a much simpler problem than current C++ proposals for ranges.
It provides a limited set of algorithms designed to be easily optimized by modern compilers
to make one pass over data that model input iterators.

Enumerators are a derived class that provide an `operator bool() const` that returns `true` when
it is still valid to dereference the iterator. This is similar to `MoveNext` in the `IEnumerator`
C# interface, but fits in better with C++ notions of iteration.

I've always wanted to be able to type `assert (exp(x) == sum(pow(x)/factorial))`. With this
library `assert (fabs(exp(x) - sum(pow(x)/factorial{}) <= 2*std::numeric_limits<double>::epsilon()))`
succeeds for `x` in the range ...

The basic idea is that `input<I,T>` is an input iterator that uses `I` for iteration and returns value_type `T`,
perhaps different from `I::value_type`.
The canonical example is applying a function from T -> U on an input iterator.
The resulting iterator should be of type input<T,U>, but we still need the original iterator
in order to do lazy evaluation.
This requires bundling up everything needed for just in time delivery.
The code is drastically simplified by passing everything by value but that tends to make iterators fat.

The class `input_base` uses template forwarding to provide an interface class.
