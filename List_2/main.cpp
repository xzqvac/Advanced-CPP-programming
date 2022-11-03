#include <iostream>
#include <cstring>
#include <cmath>

namespace cpplab
{
    // Sum of two arguments passed by pointers
    template <typename T, typename U>
    auto add(T*  x, U* y) -> decltype(x + y)
    {
        return x + y;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, const char*>::value>
    sukces(const char* x)
    {
        std::cout << x[0];
    }

    template<typename T>
    void sukces(T x)
    {
        std::cout << x;
    }
    // auto add(const char* x,const char* y)
    // {
    // char asia[80];
    // strcpy(asia, x);
    // strcat(asia, y);
//
    // return asia;
    // }
}

namespace cpplab
{
    template <typename T, T side, int dimension>
    class hyperqube
    {
    public:
        constexpr T getVolume()
        {
            T volume = 0;
            if (dimension > 0)
                return volume = std::pow(side, dimension);
            else
                return -1;
        }
    };
}

namespace cpplab{
    template <typename T, typename... Types>
    auto add_total(T first, Types... Last)
    {
        if constexpr (sizeof...(Last) == 0)
            return first;
        else
            return first + add_total(Last...);
    }
}

//https://www.geeksforgeeks.org/variadic-function-templates-c/




int main(){
    const char* first = "String";
    const char* second = "Concaneated";
//    cpplab::sukces<const char*> (first);
//    cpplab::sukces<int> (5);

    std::cout << cpplab::add_total(5.5, 2, 3.7);
    return 0;
}

