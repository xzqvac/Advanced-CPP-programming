#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>

namespace cpplab
{

    class ThreadPool
    {
    public:
        ThreadPool(std::size_t numOfThreads)
        {
            for (auto i = 0; i < numOfThreads; i++)
            {
                threads.emplace_back([=]
                                     {
                    while(true)
                    {
                        std::unique_lock<std::mutex> lock{eventMutex};
                        eventVar.wait(lock, [=] { return stop;});

                        if (stop)
                            break;
                    } });
            }
        };

        ~ThreadPool()
        {
        }

    private:
        std::vector<std::thread> threads;
        std::condition_variable eventVar;
        std::mutex eventMutex;
        bool stop = false;

        void stop()
        {
            {
                std::unique_lock<std::mutex> lock{eventMutex};
                stop = true;
            }

            eventVar.notify_all();
            for (auto& thread : threads)
                thread.join();
        }
    };
}

int main()
{
    cpplab::ThreadPool pool(10);

    return 0;
}