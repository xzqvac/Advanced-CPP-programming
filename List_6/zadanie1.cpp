#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <future>
#include <utility>


void dotProduct(std::vector<int> a, std::vector<int> b, std::promise<int>&& dotResultPromise)
{   
    dotResultPromise.set_value(std::inner_product(a.begin(), a.end(), b.begin(), 0));
} 

int main()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 5, 6};

    std::promise<int> dotProductPromise;
    std::future<int> dotProductFuture = dotProductPromise.get_future();

    std::thread t1(dotProduct, a, b, std::move(dotProductPromise));
    t1.join();

    std::cout << "OddSum : " << dotProductFuture.get() << std::endl;
    return 0;
}