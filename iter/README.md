# enumerators - iterators that know when they are done

An `enumerator` is an iterators that provides `operator bool() const`
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
will be supplied at compile time.

The convention is to use `class_` for class names and `class` instead of `make_class`. 
Users never need to use the class directly, just the corresponding template function.

The purpose is to make C++ more expressive for implementing numerical algorithms. The
bias is to assume all iterators are input iterators over constant data. The inspiration
comes from Fortran and APL, but incorporates recent functional programming notions.

## TODO

Specialize enumerator for all iterator categories, not just input iterator.

Get `is_counted` working.

operator, => concatenate

operator^ => monotonic cycle
