#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>

namespace cpplab
{
    template<typename T>
    class Vector {
    private:
        T *data_ = nullptr; // pointer to first element of vector
        size_t capacity_ = 0; // total space
        size_t size_ = 0; // amount of elements / index

    public:
        Vector() = default; // default constructor
        Vector(size_t capacity, T initial); // parameterized constructor
        Vector(std::initializer_list<T> l); // constructor with initializer list

        ~Vector() { delete[] data_; } // destructor

        T &operator[](size_t index); // return element`s reference at index
        const T operator[](size_t index) const;

        void reserveMemory(size_t capacity);

        void pushBack(const T &value);

        void pop();

        size_t size() const { return size_; } // Return amount of elements
        size_t capacity() const { return capacity_; } // Return total space
    };

// Element read/write access
    template<typename T>
    T &Vector<T>::operator[](size_t index)
    {
    try{
        if(index >= 0 < size_)
            return data_[index];
        else
            throw(index);
    }
    catch (size_t num){
        std::cout << "Index: " << num << " is out of vector`s scope" << '\n';
    }
    }

    template<typename T>
    const T Vector<T>::operator[](size_t index) const
    {
        if (index >= 0 && index < size_)
            return data_[index];
    }

    template<typename T>
    Vector<T>::Vector(size_t capacity, T initial): capacity_(capacity), size_{capacity}, data_{new T[capacity]{}}
    {
        for (size_t i = 0; i < capacity; i++)
            data_[i] = initial;
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> l) : capacity_(l.size()), size_{l.size()}, data_{new T[l.size()]{}} {
        std::copy(l.begin(), l.end(), data_);
    }

// Change vector`s memory/capacity
    template<typename T>
    void Vector<T>::reserveMemory(size_t newCapacity) {

        if (newCapacity < size_) // if vector`s elements--
            size_ = newCapacity;

        T *newBlock = new T[newCapacity];

        for (size_t i = 0; i < size_; i++)  // moving data_ from one vector to other
            newBlock[i] = data_[i];
        delete[] data_;
        data_ = newBlock;
        capacity_ = newCapacity;
    }

// Add element at end of vector
    template<typename T>
    void Vector<T>::pushBack(const T &value) {
        if (size_ >= capacity_)
            reserveMemory(capacity_ * 2);

        data_[size_] = value;
        size_++;
    }

// Delete element at end of vector
    template<typename T>
    void Vector<T>::pop() {
        try {
            if (size_ >= 1) {
                size_--;
                data_[size_].~T();
            } else
                throw (size_);
        }
        catch (size_t num) {
            std::cout << "Nothing to pop, because vector has size of: " << num << '\n';
        }

    }

    template<typename T>
    void printVector(Vector<T> &vector) {
        for (size_t i = 0; i < vector.size(); i++)
            std::cout << vector[i] << '\n';
        std::cout << "------------------------" << '\n';
    }
}

template <typename T, typename U>
auto operator*(T const  &a, U const &b)
{
    auto result = a[0] * b[0];
    if(a.size() == b.size())
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
    cpplab::Vector<int> vector = {1, 2, 3};
    printVector(vector);

    cpplab::Vector<int> vector_of_ones(3, 1);
    printVector(vector_of_ones);

    vector_of_ones.pushBack(1);
    printVector(vector_of_ones);

    vector_of_ones.pop();
    vector_of_ones.pop();
    printVector(vector_of_ones);

    cpplab::Vector<int> v1 = {1, 2, 3};
    cpplab::Vector<int> v2 = {3, 2, 1};
    std::vector<int> v3 = {3, 1, 2};
    std::cout << v1 * v2 << '\n';
    std::cout << v1 * v3 << '\n';

    return 0;
}
