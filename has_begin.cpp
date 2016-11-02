#include <iostream>
#include <type_traits>

template<class C>
struct HasBegin {
    template<class T, T>
    struct TypeCheck {
    };

    template<class T>
    struct Signature {
        using Type = void (T::*)();
    };

    template<class T>
    using Check = TypeCheck<typename Signature<T>::Type, &T::begin>;

    template<class T> static std::true_type check(Check<T> *);
    template<class T> static std::false_type check(...);

    constexpr static bool value = std::is_same<std::true_type, decltype(check<C>(nullptr))>::value;
};

struct A {
};

struct B {
    void begin();
};

int main()
{
    std::cout << "A: " << HasBegin<A>::value << std::endl;
    std::cout << "B: " << HasBegin<B>::value << std::endl;
}
