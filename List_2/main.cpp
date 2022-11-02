#include <iostream>
#include <cstring>

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

int main(){
    const char* first = "String";
    const char* second = "Concaneated";
    cpplab::sukces<const char*> (first);
    cpplab::sukces<int> (5);

    return 0;
}

