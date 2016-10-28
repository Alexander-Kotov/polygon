#include <iostream>
#include <random>

struct GeneratorBase {
    static void setUp();
    static void tearDown();
};

void GeneratorBase::setUp()
{
}

void GeneratorBase::tearDown()
{
}

// генераторы значений
template<class T>
struct Generator : GeneratorBase {
    static T getValue();
};

template<class T>
struct Generator<const T &> : GeneratorBase {
    static T getValue();
};

template<class T>
struct Generator<T &&> : GeneratorBase {
    static T getValue();
};

template<>
int Generator<int>::getValue()
{
    static std::random_device device;
    static std::mt19937 generator(device());

    return generator();
}

template<>
std::string Generator<const std::string &>::getValue()
{
    static std::random_device device;
    static std::mt19937 generator(device());
    std::uniform_int_distribution<size_t> size_dist(0, 13);
    std::uniform_int_distribution<unsigned> char_dist(0, 25);

    std::string s;
    s.resize(size_dist(generator));
    for(char &c : s) {
        c = "abcdefghijklmnopqrstuvwxyz"[char_dist(generator)];
    }

    return s;
}

// вспомогательная функция. заставляет вычислить значения
template<class... T>
void swallow(T &&...)
{
}

template<class R, class... Args>
void run(R (*func)(Args...))
{
    swallow((Generator<Args>::setUp(), 0)...);
    for(unsigned i = 0; i < 10; ++i) {
        func(Generator<Args>::getValue()...);
    }
    swallow((Generator<Args>::tearDown(), 0)...);
}

// тестируемая функция
int foo(int a, const std::string &b, int c)
{
    static unsigned n = 1;
    std::cout << n << ") a=" << a << ", b=\"" << b << "\", c=" << c << std::endl;
    ++n;
    return 0;
}

int main()
{
    run(foo);
}
