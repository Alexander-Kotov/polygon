#include <iostream>
#include <map>
#include <string>
#include <type_traits>

//
// макросы для генерации уникального имени
//
#define UNIQUE_NAME_CONCAT0(a, b) a##b
#define UNIQUE_NAME_CONCAT(a, b)  UNIQUE_NAME_CONCAT0(a, b)
#define UNIQUE_NAME(prefix)       UNIQUE_NAME_CONCAT(prefix, __LINE__)

//
// макрос для определения класса-обёртки c нужными методами
//
#define MAP_VALUE_TYPE_WRAPPER(type, pair, getKey, getValue) \
    class type { \
    public: \
        type(pair &p) : p{p} {} \
        \
        typename pair::first_type &getKey() { return p.first; } \
        std::conditional_t<std::is_const<pair>::value, const typename pair::second_type, typename pair::second_type> &getValue() { return p.second; } \
        \
    private: \
        pair &p; \
    }

//
// вспомогательный макрос для range-for
//
#define FOR_(var, key, value, pairs) \
    MAP_VALUE_TYPE_WRAPPER(UNIQUE_NAME(PairWrapper), std::remove_reference_t<decltype(*pairs.begin())>, key, value); \
    for (UNIQUE_NAME(PairWrapper) var : pairs)

void foo(const std::map<int, std::string> &m)
{
    FOR_(b, const_key, const_value, m) {
        std::cout << b.const_key() << ", " << b.const_value() << std::endl;
    }
}

void bar(std::map<int, std::string> &m)
{
    FOR_(b, key, value, m) {
        b.value() += b.value();
    }
}

int main()
{
    std::map<int, std::string> m {
        {4, "четыре"},
        {-7, "минус семь"},
        {13, "чёртова дюжина"},
        {92, "девяносто два и ноль эфэм"}
    };

    //
    // для доступа к ключам и значениям можно использовать осмысленные имена
    //
    FOR_(b, code, message, m) {
        std::cout << b.code() << ", " << b.message() << std::endl;
    }

    bar(m);

    FOR_(b, key, value, m) {
        std::cout << b.key() << ", " << b.value() << std::endl;
    }

    foo(m);
}
