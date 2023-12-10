#include <iostream>

template <typename T>
class SimpleVector
{
public:
    SimpleVector() : size(0), capacity(1), array(new T[1]) {}

    ~SimpleVector()
    {
        delete[] array;
    }

    void pushBack(const T &element)
    {
        if (size == capacity)
        {
            resize();
        }
        array[size++] = element;
    }

    T &operator[](size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of bounds");
        }
        else if (index < 0)
        {
            throw std::out_of_range("Index can not be negative");
        }
        // No bounds checking for simplicity. Be cautious not to go out of bounds.
        return array[index];
    }

    size_t getSize() const
    {
        return size;
    }

private:
    void resize()
    {
        capacity *= 2;
        T *newArray = new T[capacity];
        for (size_t i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }

    T *array;
    size_t size;
    size_t capacity;
};