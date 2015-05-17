# iter - input iterator for numerics

An `enumerator` is an iterators that provides `operator bool() const` which returns `true` when
it is valid to dereference the iterator.
This is similar to `MoveNext` in the `IEnumerator`
C# interface, but fits in better with C++ notions of iteration.
If the iterator has an end it behaves like `i != end`.

The basic idea is that `enumerator<I,T>` is an iterator that uses `I` for iteration and returns value_type `T`,
perhaps different from `I::value_type`.
The canonical example is applying a function from T → U on an input iterator.
The resulting iterator should be of type `enumerator<T,U>`.


All classes deriving from `enumerator_base` are quite simple: save the iterator an necessary
accoutrements then implement `operator bool`, `operator*`, and `operator++` pre and post increment. 
That's all! 

The convention is to use `class_` for class names and `class` instead of `make_class`. Users never
need to use the class directly, just the corresponding template function.

operator, => concatenate

operator^ => monotonic cycle
