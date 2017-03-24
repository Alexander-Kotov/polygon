#include <cstddef>
#include <iostream>
#include <typeinfo>

template<size_t... k>
struct IndexPack {
};

template<size_t m, class P>
struct Append;

template<size_t m, size_t... k>
struct Append<m, IndexPack<k...>> {
    using Type = IndexPack<m, k...>;
};

template<size_t b, size_t e>
struct IndexRange {
    using Type = typename Append<b, typename IndexRange<b + 1, e>::Type>::Type;
};

template<size_t e>
struct IndexRange<e, e> {
    using Type = IndexPack<>;
};

template<char... c>
struct CharSequence {
};

template<size_t n>
constexpr size_t length(const char (&)[n])
{
    return n - 1;
}

template<const char *s, class P>
struct Extract;

template<const char *s, size_t... k>
struct Extract<s, IndexPack<k...>> {
    using Type = CharSequence<s[k]...>;
};

constexpr const char abcde[] = "abcde";

int main()
{
    using namespace std;

    typename Extract<abcde, typename IndexRange<0, length(abcde)>::Type>::Type _;

    cout << typeid(_).name() << endl;
}
