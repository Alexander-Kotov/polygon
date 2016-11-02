#include "index_tuple.h"

template<class... T>
struct TypeTuple {
};

template<class U, size_t n>
struct Pair {
};

template<class T, class I>
struct Zipper;

template<class ...T, size_t... n>
struct Zipper<TypeTuple<T...>, IndexTuple<n...>> {
    using type = TypeTuple<Pair<T, n>...>;
};

template<class... T>
struct TypeIndexBuilder {
    using type = typename Zipper<TypeTuple<T...>, typename IndexTupleBuilder<sizeof...(T)>::type>::type;
};

template<size_t, class... T>
struct ExtractType;

template<class T, class... U>
struct ExtractType<0, T, U...> {
    using type = T;
};

template<size_t n>
struct ExtractType<n> {
    struct Invalid_Index;

    using type = Invalid_Index;
};

template<size_t n, class T, class... U>
struct ExtractType<n, T, U...> {
    using type = typename ExtractType<n - 1, U...>::type;
};

template<class T>
struct DebugType;

int main()
{
    //DebugType<typename ExtractType<4, int, char, void *>::type> _;
    //DebugType<typename TypeIndexBuilder<int, char, void *>::type> _;
}
