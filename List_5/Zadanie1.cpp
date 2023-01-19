#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <cassert>
#include <thread>
#include <mutex>

int threadID()
{
    thread_local int threadID = 0;
    static int g_ID = 0;
    static std::mutex mtx;
    std::lock_guard lock(mtx);
    threadID = g_ID++;
    return threadID;
}

namespace cpplab
{   
    void printThreadID()
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << threadID() << '\n';
    }
    class Pixel
    {
    public:
        Pixel(){};
        ~Pixel() {};
        int r_, g_, b_;
        Pixel(int r, int g, int b)
        {
            r_ = r;
            g_ = g;
            b_ = b;
        }

        Pixel(const Pixel& another)
        {
            r_ = another.r_;
            g_ = another.g_;
            b_ = another.b_;
        }
    };
    template <typename T>
    class Vector
    {
    public:
        T* data_ = nullptr;   // pointer to first element of vector
        size_t capacity_ = 0; // total space
        size_t size_ = 0;     // amount of elements / index
        Vector() = default;                                    // default constructor
        Vector(size_t capacity, T initial);                    // parameterized constructor
        Vector(std::initializer_list<T> l);                    // constructor with initializer list
        Vector(const Vector<T>& another_vector);               // copy constructor
        Vector<T>& operator=(const Vector<T>& another_vector); // copy assignment
        Vector(Vector<T>&& another_vector) noexcept; // move constructor
        Vector<T>& operator=(Vector<T>&& another_vector) noexcept;// move assignment

        ~Vector() { delete[] data_; } // destructor

        T& operator[](size_t index); // return element`s reference at index
        const T operator[](size_t index) const;
        void reserveMemory(size_t capacity);
        void pushBack(const T& value);
        void pop();
        //void emplace_back(T args);
        size_t size() const { return size_; }         // Return amount of elements
        size_t capacity() const { return capacity_; } // Return total space
    

    template <typename ... Ts>
    void emplace_back(Ts&& ... args)
    {
        if (size_ >= capacity_)
            reserveMemory(capacity_ * 2);
        data_[size_] = T(std::forward<Ts>(args)...);
        size_++;
    }
    };
    template <typename T>
    Vector<T> operator+(const Vector<T>& a,const Vector<T>& b)
    {
        Vector<T> result = a;
        for (int i = 0; i < result.size(); i++)
            result[i] += b[i];
        return result;
    }

    // Element read/write access
    template <typename T>
    T& Vector<T>::operator[](size_t index)
    {
        try
        {
            if (index >= 0 < size_)
                return data_[index];
            else
                throw(index);
        }
        catch (size_t num)
        {
            std::cout << "Index: " << num << " is out of vector`s scope" << '\n';
        }
    }

    // Operator []
    template <typename T>
    const T Vector<T>::operator[](size_t index) const
    {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    // Copy constructor
    template <typename T>
    Vector<T>::Vector(const Vector<T>& another_vector)
    {
        std::cout << "Copy constructor" << std::endl;
        size_ = another_vector.size();
        capacity_ = another_vector.capacity();
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = another_vector[i];
    }

    //Move Constructor
    template <typename T>
    Vector<T>::Vector(Vector<T>&& another_vector) noexcept
    {
        std::cout << "Move constructor" << std::endl;
        capacity_ = another_vector.capacity();
        size_ = another_vector.size();
        data_ = another_vector.data_;
        
        another_vector.capacity_ = 0;
        another_vector.size_ = 0;
        another_vector.data_ = nullptr;
    }
    // Copy assignment
    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& another_vector)
    {
        std::cout << "Copy assignment" << std::endl;
        if (this == &another_vector) // prevent before deleting own data
            return *this;
        delete[] data_; // deleting data, because in next step we arrange new addres for it 
        size_ = another_vector.size();
        capacity_ = another_vector.capacity();
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = another_vector[i];
        return *this;
    }

    // Move assignment
    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& another_vector) noexcept
    {
        std::cout << "Move assignment" << std::endl;
        delete[] data_;
        size_ = another_vector.size();
        capacity_ = another_vector.capacity();
        data_ = another_vector.data_;

        another_vector.capacity_ = 0;
        another_vector.size_ = 0;
        another_vector.data_ = nullptr;

        return *this;
    }

    // parameterized constructor
    template <typename T>
    Vector<T>::Vector(size_t capacity, T initial) : capacity_(capacity), size_{ capacity }, data_{ new T[capacity]{} }
    {
        std::cout << "Parameterized constructor" << std::endl;
        for (size_t i = 0; i < capacity; i++)
            data_[i] = initial;
    }

    //constructor with initializer list
    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> l) : capacity_(l.size()), size_{ l.size() }, data_{ new T[l.size()]{} }
    {
        std::cout << "Constructor with initializer list" << std::endl;
        std::copy(l.begin(), l.end(), data_);
    }

    // Change vector`s memory/capacity
    template <typename T>
    void Vector<T>::reserveMemory(size_t newCapacity)
    {

        if (newCapacity < size_) // if vector`s elements--
            size_ = newCapacity;

        T* newBlock = new T[newCapacity];

        for (size_t i = 0; i < size_; i++) // moving data_ from one vector to other
            newBlock[i] = data_[i];
        delete[] data_;
        data_ = newBlock;
        capacity_ = newCapacity;
    }

    // Add element at end of vector
    template <typename T>
    void Vector<T>::pushBack(const T& value)
    {
        if (size_ >= capacity_)
            reserveMemory(capacity_ * 2);

        data_[size_] = value;
        size_++;
    }

    // Delete element at end of vector
    template <typename T>
    void Vector<T>::pop()
    {
        try
        {
            if (size_ >= 1)
            {
                size_--;
                data_[size_].~T();
            }
            else
                throw(size_);
        }
        catch (size_t num)
        {
            std::cout << "Nothing to pop, because vector has size of: " << num << '\n';
        }
    }

    template <typename T>
    void printVector(const Vector<T>& vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
            std::cout << vector[i] << '\n';
        std::cout << "------------------------" << '\n';
    }
}

template <typename T, typename U>
auto operator*(T const& a, U const& b)
{
    auto result = a[0] * b[0];
    if (a.size() == b.size())
    {
        for (int i = 1; i < a.size(); i++)
            result += a[i] * b[i];
    }
    else
        std::cout << "They are not the same size" << '\n';
    return result;
}


int main()
{
    //cpplab::Vector<int> vector; // default constructor

    //cpplab::Vector<int> vector_0 = { 1, 2, 3 }; // constructor with initializer list

    //cpplab::Vector<int> vector_1 = vector_0; // copy constructor

    //cpplab::Vector<int> vector_2(vector_0); // copy constructor

    //cpplab::Vector<int>* vector_3 = new cpplab::Vector<int>(vector_0); // copy constructor 

    //cpplab::Vector<int>* vector_4 = new cpplab::Vector<int>(std::move(vector_0 + vector_0)); // move constructor

    //cpplab::Vector<int> vector_6;
    //vector_6 = (std::move(vector_0 + vector_0));

    std::thread thread_1(cpplab::printThreadID);
    std::thread thread_2(cpplab::printThreadID);
    std::thread thread_3(cpplab::printThreadID);

    thread_1.join();
    thread_2.join();
    thread_3.join();
    
    return 0;
}