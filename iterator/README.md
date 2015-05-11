# Iterator - input iterator classes for numerics

The basic idea is that input<I,T> uses I for iteration and returns value_type T perhaps different from I::value_type.
The canonical example is applying a function from T -> U. The resulting iterator should be of type input<T,U>.
All iterators are value types and lazily evaluate.

