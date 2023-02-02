#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <future>
#include <utility>


void dotProduct(std::vector<int> a, std::vector<int> b, std::promise<int>&& dotResultPromise)
{   
    try
    {
        if (a.size() == 0 || b.size() == 0)
            throw std::logic_error("Empty vector");
        if (a.size() != b.size())
            throw std::logic_error("Different sizes");
        dotResultPromise.set_value(std::inner_product(a.begin(), a.end(), b.begin(), 0));
    }
    catch(const std::exception& e)
    {
        dotResultPromise.set_exception(std::current_exception());
    }
} 

int main()
{
    size_t threadsAmount = 10;
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 5, 6};

    std::vector<std::promise<int>> promises;
    std::vector<std::future<int>> futures;
    std::vector<std::thread> threads;

    for(size_t i = 0; i < threadsAmount; i++)
    {
        promises.push_back(std::promise<int>());
        futures.push_back(promises.back().get_future());
        threads.push_back(std::thread(dotProduct, a, b, std::move(promises.back())));
    }

    int sumOfProducts = 0;
    for(size_t i = 0; i < threadsAmount; i++)
    {
        try{
            sumOfProducts += futures[i].get();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "\n";
        }
        threads[i].join();        
    }
    
    std::cout << sumOfProducts << std::endl;

    //std::promise<int> dotProductPromise;
    //std::future<int> dotProductFuture = dotProductPromise.get_future();

    //std::thread t1(dotProduct, a, b, std::move(dotProductPromise));
    //t1.join();

    //std::cout << "OddSum : " << dotProductFuture.get() << std::endl;
    //return 0;
}