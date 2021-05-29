#include <iostream>

using namespace std;

template <class T>
class Stack
{
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    T& Top() const;
    bool IsEmpty() const;
    void Push(const T& x);
    void Pop();
    void ChangeSize1D(T*& a, const int oldSize, const int newSize);
private:
    T *Array;
    int capacity;
    int top;
};

template <class T>
Stack<T>::~Stack()
{
    delete [] Array;
}

template <class T>
Stack<T>::Stack(int bagCapacity)
:capacity(bagCapacity)
{
    if (capacity < 1)
        throw "Capacity must be > 0";
    Array = new T[capacity];
    top = -1;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return (top + 1 == 0);
}

template <class T>
void Stack<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);

    delete [] a;
    a = temp;
}

template <class T>
void Stack<T>::Push(const T& x)
{
    if (capacity == top + 1) {
        ChangeSize1D(Array, capacity, capacity * 2);
        capacity *= 2;
    }
    Array[++top] = x;
}

template <class T>
T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty.";
    return Array[top];
}

template <class T>
void Stack<T>::Pop()
{
    if(IsEmpty()) throw "Stack is empty, cannot delete.";
    Array[top--].~T();
}


