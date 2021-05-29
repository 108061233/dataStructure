#include<iostream>

using namespace std;

template <class T>
class Queue
{
public:
    Queue (int queueCapacity = 10);
    bool IsEmpty();
    T& Front();
    T& Rear();
    void Push (const T& x);
    void Pop();
    void ChangeCapacity();
private:
    int FRONT;
    int REAR;
    int capacity;
    T* QUEUE;
};

template <class T>
Queue<T>::Queue(int queueCapacity)
:capacity(queueCapacity)
{
    FRONT = 0;
    REAR = 0;
    QUEUE = new T[capacity];
}

template <class T>
inline bool Queue<T>::IsEmpty()
{
    return (FRONT == REAR);
}

template <class T>
inline T& Queue<T>::Front()
{
    if (IsEmpty()) throw "Queue is empty.";
    return QUEUE[(FRONT + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
    if (IsEmpty()) throw "Queue is empty.";
    return QUEUE[REAR];
}

template <class T>
void Queue<T>::ChangeCapacity()
{
    T* newQueue = new T[2 * capacity];

    int start = (FRONT + 1) % capacity;
    if (start < 2)
        copy(QUEUE + start, QUEUE + start + capacity - 1, newQueue);
    else {
        copy(QUEUE + start, QUEUE + capacity, newQueue);
        copy(QUEUE, QUEUE + REAR + 1, newQueue + capacity - start);
    }

    FRONT = 2 * capacity - 1;
    REAR = capacity - 2;
    capacity *= 2;
    delete [] QUEUE;
    QUEUE = newQueue;
}

template <class T>
void Queue<T>::Push(const T& x)
{
    if ((REAR + 1) % capacity == FRONT) ChangeCapacity();
    REAR = (REAR + 1) % capacity;
    QUEUE[REAR] = x;
}

template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    else {
        FRONT = (FRONT + 1) % capacity;
        QUEUE[FRONT].~T();
    }
}
