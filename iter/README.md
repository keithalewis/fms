# iter - iterators that know when they are done

An `enumerator` is an iterators that provides `operator bool() const`
which returns `true` when it is valid to dereference the iterator.
This is similar to `MoveNext` in the `IEnumerator` C# interface,
but fits in better with C++ notions of iteration.
If the iterator has an end it behaves like `i != end`.

The basic idea is that `enumerator<I,T>` is an iterator
that uses `I` for iteration and returns value_type `T`,
perhaps different from `I::value_type`.
The canonical example is applying a function from T → U on an input iterator.
The resulting iterator should be of type `enumerator<T,U>`.


All classes deriving from `enumerator` are quite simple: save the
iterator and necessary accoutrements in the constructor then implement
`operator bool`, `operator*`, and `operator++` pre and post increment. 
These hide the implementation in the base class, but enumerator
algorithms pass everything by value so the correct implementation
will be called.

The convention is to use `class_` for class names and `class` instead of `make_class`. 
Users never need to use the class directly, just the corresponding template function.

operator, => concatenate

operator^ => monotonic cycle
