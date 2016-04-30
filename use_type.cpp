#include <type_traits>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template<class T, bool>
struct TypeSelector {
    typedef string Type; // тип по умолчанию
};

template<class T>
struct TypeSelector<T, true> {
    typedef typename T::Type Type; // используется определение из класса
};

template<class T>
struct HasType {
    template<class U> static true_type tryUseType(typename U::Type *);
    template<class U> static false_type tryUseType(...);

    static const bool value = is_same<decltype(tryUseType<T>(nullptr)), true_type>::value;
};

template<class T>
struct UseType {
    typedef typename TypeSelector<T, HasType<T>::value>::Type type;
};

//
// классы пользователя
//

struct A {
};

struct B {
    typedef vector<char> Type;
};

//
// вспомогательные классы вида is_<что-то>
//

template<class T>
struct is_string : public is_same<string, T> {
};

template<class T>
struct is_vector : public is_same<vector<char>, T> {
};

int main()
{
    UseType<A>::type s = "abcdef";
    cout << "s='" << s << "'" << endl;

    cout << boolalpha;
    cout << is_string<UseType<A>::type>::value << endl;
    cout << is_vector<UseType<B>::type>::value << endl;
}
