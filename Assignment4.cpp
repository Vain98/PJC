#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <cstring>

template <typename T>
class MyVector
{
private:
    T *arr;
    std::size_t size;
    std::size_t cap;

public:
    MyVector();
    MyVector(const MyVector &vec);
    MyVector(MyVector &&vec);
    ~MyVector();
    void operator=(const MyVector &vec);
    void operator=(MyVector &&vec);
    T operator[](std::size_t index) const;
    T &operator[](std::size_t index);
    std::size_t getSize() const;
    std::size_t getCapacity() const;
    void insert(std::size_t index, const T elems[], std::size_t sz);
    void insert(std::size_t index, const T &elem);
    void append(const T elems[], std::size_t sz);
    void append(const T &elem);
    std::size_t remove(const T &elem, std::size_t from = 0);
    bool removeAll(const T &elem, std::size_t from = 0);
    bool copyable();

public:
    template <typename>
    friend std::ostream &operator<<(std::ostream &output_stream, const MyVector<T> &vec);
};

template <typename T>
MyVector<T>::MyVector()
        : cap(2), size(0)
{
    arr = new T[cap];
}

template <typename T>
MyVector<T>::MyVector(const MyVector &vec)
        : cap(vec.cap), size(vec.size)
{

    arr = new T[cap];

    for (std::size_t i = 0; i < vec.size; i++)
        arr[i] = vec.arr[i];
}

template <typename T>
MyVector<T>::MyVector(MyVector &&vec)
{
    if (this != &vec)
    {
        delete[] arr;

        cap = vec.cap;
        size = vec.size;

        for (std::size_t i = 0; i < vec.size; i++)
            arr[i] = vec.arr[i];
    }
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] arr;

}

template <typename T>
void MyVector<T>::operator=(const MyVector &vec)
{

    if (size < vec.size)
    {
        cap = vec.cap;
        size = vec.size;

        delete[] arr;
        arr = new T[cap];
    }

    for (std::size_t i = 0; i < vec.size; i++)
        arr[i] = vec.arr[i];
}

template <typename T>
void MyVector<T>::operator=(MyVector &&vec)
{
    if (this != &vec)
    {
        delete[] arr;

        arr = new T[vec.cap];

        for (std::size_t i = 0; i < vec.size; i++)
            arr[i] = vec.arr[i];
    }
}

template <typename T>
T MyVector<T>::operator[](std::size_t index) const
{
    if (index >= cap || index < 0)
        throw std::out_of_range("T MyVector<T>::operator[](std::size_t) const -> Index out of range");

    return arr[index];
}

template <typename T>
T &MyVector<T>::operator[](std::size_t index)
{
    if (index >= cap || index < 0)
        throw std::out_of_range("T& MyVector<T>::operator[](std::size_t) -> Index out of range");
    return arr[index];
}

template <typename T>
std::size_t MyVector<T>::getSize() const
{
    return size;
}

template <typename T>
std::size_t MyVector<T>::getCapacity() const
{
    return cap;
}

template <typename T>
void MyVector<T>::insert(std::size_t index, const T elems[], std::size_t sz)
{
    if (index > cap || index < 0)
        throw std::out_of_range("void MyVector<T>::insert(std::size_t, const T[], std::size_t) -> Index out of range");

    if (cap > sz + size)
    {
        size_t index2 = 0;
        for (std::size_t i = size; i >= index; i--)
        {
            arr[i + sz] = arr[i];
        }

        for (std::size_t i = index; i < index + sz; i++)
        {
            arr[i] = elems[index2];
            index2++;
        }

        size += sz;
    }

    else
    {
        cap = (size + sz) * 2;
        size_t index2 = 0;
        T *array = new T[cap];

        for (size_t i = 0; i < index; i++)
        {
            array[i] = arr[i];
        }

        for (std::size_t i = index; i < index + sz; i++)

        for (std::size_t i = index + sz; i <= size + sz; i++)
            array[i] = arr[i];
        delete[] arr;
        arr = array;
        size += sz;
    }
}

template <typename T>
void MyVector<T>::insert(std::size_t index, const T &elem)
{
    if (index >= cap || index < 0)
        throw std::out_of_range("void MyVector<T>::insert(std::size_t, const T&) -> Index out of range");

    if (cap > size + 1)
    {
        if (size != 0)
        {
            for (std::size_t i = size; i >= index; i--)
                arr[i + 1] = arr[i];
            arr[index] = elem;

            size++;
        }

        else
        {
            arr[index] = elem;
            size++;
        }
    }

    else
    {
        cap = (size + 1) * 2;
        T *array = new T[cap];

        for (size_t i = 0; i < index; i++)
        {
            array[i] = arr[i];
        }

        for (std::size_t i = size + 1; i >= index; i--)
            array[i + 1] = arr[i];

        array[index] = elem;
        delete[] arr;
        arr = array;
        size++;
    }
}

template <typename T>
void MyVector<T>::append(const T elems[], std::size_t sz)
{
    if (size + sz <= cap)
    {
        for (std::size_t i = size; i < size + sz; i++)
            arr[i] = elems[i];
        size += sz;
    }

    else
    {
        cap = (cap + sz + size) * 2;

        T *temp = new T[size];

        for (std::size_t i = 0; i < size; i++)
            temp[i] = arr[i];

        delete[] arr;

        arr = new T[cap];

        for (std::size_t i = 0; i < size; i++)
            arr[i] = temp[i];

        delete[] temp;

        for (std::size_t i = size; i < size + sz + 1; i++)
            arr[i] = elems[i];

        size += sz;
    }
}

template <typename T>
void MyVector<T>::append(const T &elem)
{
    if (size + 1 < cap)
        arr[size++] = elem;

    else
    {
        cap = (cap + size + 1) * 2;

        T *temp = new T[size];

        for (std::size_t i = 0; i < size; i++)
            temp[i] = arr[i];

        arr = new T[cap];

        for (std::size_t i = 0; i < size; i++)
            arr[i] = temp[i];

        delete[] temp;

        arr[size++] = elem;
    }
}

template <typename T>
std::size_t MyVector<T>::remove(const T &elem, std::size_t from)
{
    int counter = 0;
    std::size_t position = 0;

    if (from > cap || from < 0)
        throw std::out_of_range("std::size_t MyVector<T>::remove(const T&, std::size_t = 0) -> Index out of range");

    T *temp = new T[size];

    for (std::size_t i = 0; i < from; i++)
        temp[i] = arr[i];

    for (std::size_t i = from, j = from; i < size; i++, j++)
    {
        temp[j] = arr[i];

        if (arr[i] == elem && counter != 1)
        {j--;
            counter++;
            position = i;
        }
    }

    return position;
}

template <typename T>
bool MyVector<T>::removeAll(const T &elem, std::size_t from)
{
    std::size_t actual_size = size;

    for (std::size_t i = from; i < size; i++)
        if (from + 1 < size)
            remove(elem, from++);

    return size != actual_size;
}

template <typename T>
bool MyVector<T>::copyable()
{

    return std::is_trivially_copyable<T>::value;
}

template <typename T>
std::ostream &operator<<(std::ostream &output_stream, const MyVector<T> &vec)
{
    output_stream << "(" << vec.getSize() << "/" << vec.getCapacity() << ") ";

    for (std::size_t i = 0; i < vec.getSize(); i++)
    {
        // if i equals to 0
        if (i == 0)
            output_stream << "[ ";

        if (i < vec.getSize() - 1)
            output_stream << vec[i] << ", ";
        else // if i equals to last index
            output_stream << vec[i] << " ]" << std::endl;
    }

    return output_stream;
}

int main()
{
    int a[]{1, 2};
    MyVector<int> vi;

    std::cout << "*0* " << vi << std::endl;

    vi.insert(1, a, 2);
    std::cout << "*1* " << vi << std::endl;

    vi.insert(2, a, 2);
    std::cout << "*2* " << vi << std::endl;

    vi.insert(2, &a[1], 1);
    std::cout << "*3* " << vi << std::endl;

    vi.append(a, 2);
    vi.append(3);
    vi.append(4);
    std::cout << "*4* " << vi << std::endl;

    vi.removeAll(2);
    std::cout << "*5* " << vi << std::endl;

    size_t res = vi.remove(1);
    std::cout << "*6* " << vi << " "

              << "res=" << res << std::endl;
    res = vi.remove(4);
    std::cout << "*7* " << vi << " "
              << "res=" << res << std::endl;

    return 0;
}