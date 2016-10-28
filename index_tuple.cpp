#include <cstddef>

template<size_t... values>
struct IndexTuple {
};

template<class T1, class T2>
struct IndexTupleConcat;

template<size_t... v1, size_t... v2>
struct IndexTupleConcat<IndexTuple<v1...>, IndexTuple<v2...>> {
    using type = IndexTuple<v1..., (v2 + sizeof...(v1))...>;
};

template<size_t n>
struct IndexTupleBuilder : IndexTupleConcat<typename IndexTupleBuilder<n / 2>::type, typename IndexTupleBuilder<n - n / 2>::type> {
};

template<>
struct IndexTupleBuilder<1> {
    using type = IndexTuple<0>;
};

template<>
struct IndexTupleBuilder<0> {
    using type = IndexTuple<>;
};

template<class T>
struct DebugType;

int main()
{
    //DebugType<typename IndexTupleBuilder<5>::type> _;
}
