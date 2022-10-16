#include <iostream>

namespace cpplab
{
    // Sum of two arguments
    template <typename T, typename U>
    auto add(T x, U y) -> decltype(x + y)
    {
        return x + y;
    }

    template <typename A, typename B, typename C>
    auto alias(A x, B y, C o) -> decltype (o(x, y))
    {
        return o(x, y);
    }
}

int main()
{
    std::cout<<cpplab::add(1, 3) << '\n';
    std::cout<<cpplab::add(2.1, 2.7) << '\n';
    std::cout<<cpplab::add('A', 2) << '\n';
    std::cout<<cpplab::add(std::string("c"), std::string("pp")) << '\n';

    std::cout<<cpplab::alias(1, 2, cpplab::add<int, int>) << '\n';
    std::cout<<cpplab::alias(5, 10, [](auto a, auto b){return a > b ? a : b;}) << '\n';
    std::cout<<cpplab::alias("ABC", "DEF", [](auto a, auto b){return a > b ? a : b;}) << '\n';

    return 0;
}