#include <iostream>

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
    void Print();
    int Size();
    int Capacity();
    Queue<T> Concat(Queue<T> &b);
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
inline int Queue<T>::Capacity()
{
    return capacity;
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

template <class T>
void Queue<T>::Print()
{
    int n = 1;
    if (REAR > FRONT)
        for (int i = FRONT + 1; i <= REAR; i++) {
            cout << "Element" << " " << n << ":" << QUEUE[i] << endl;
            n++;
        }
    else if (REAR < FRONT) {
        n = 1;
        for (int i = FRONT + 1; i <= REAR + capacity; i++) {
            cout << "Element" << " " << n << ":" << QUEUE[i % capacity] << endl;
            n++;
        }
    }
    else cout << "Queue is empty.";
}

template <class T>
int Queue<T>::Size()
{
    if (REAR == FRONT) return 0;
    else if (REAR > FRONT) return REAR - FRONT;
    else return (REAR + capacity) - FRONT;
}

template <class T>
Queue<T> Queue<T>::Concat(Queue<T> &b)
{
    Queue<T> c(capacity + b.capacity);
    if (IsEmpty()) c = b;
    else if (b.IsEmpty()) c = *this;
    else if (REAR > FRONT)
        if (b.REAR > b.FRONT) {
            int i = FRONT + 1, j = b.FRONT + 1;
            for (; i <= REAR && j <= b.REAR; i++, j++) {
                c.Push(QUEUE[i]);
                c.Push(b.QUEUE[j]);
            }
            if (i - FRONT <= Size())
                for (; i <= REAR; i++) c.Push(QUEUE[i]);
            if (j - b.FRONT <= b.Size())
                for (; j <= b.REAR; j++) c.Push(b.QUEUE[j]);
        } else {
            int i = FRONT + 1, j = b.FRONT + 1;
            for (; i <= REAR && j <= b.REAR + b.capacity; i++, j++) {
                c.Push(QUEUE[i]);
                c.Push(b.QUEUE[j % b.capacity]);
            }
            if (i - FRONT <= Size())
                for (; i <= REAR; i++) c.Push(QUEUE[i]);
            if (j - b.FRONT <= b.Size())
                for (; j <= b.REAR + b.capacity; j++) c.Push(b.QUEUE[j % b.capacity]);
        }
    else {
         if (b.REAR > b.FRONT) {
            int i = FRONT + 1, j = b.FRONT + 1;
            for (; i <= REAR + capacity && j <= b.REAR; i++, j++) {
                c.Push(QUEUE[i % capacity]);
                c.Push(b.QUEUE[j]);
            }
            if (i - FRONT <= Size())
                for (; i <= REAR + capacity; i++) c.Push(QUEUE[i % capacity]);
            if (j - b.FRONT <= b.Size())
                for (; j <= b.REAR; j++) c.Push(b.QUEUE[j]);
        } else {
            int i = FRONT + 1, j = b.FRONT + 1;
            for (; i <= REAR + capacity && j <= b.REAR + b.capacity; i++, j++) {
                c.Push(QUEUE[i % capacity]);
                c.Push(b.QUEUE[j % b.capacity]);
            }
            if (i - FRONT <= Size())
                for (; i <= REAR + capacity; i++) c.Push(QUEUE[i % capacity]);
            if (j - b.FRONT <= b.Size())
                for (; j <= b.REAR + b.capacity; j++) c.Push(b.QUEUE[j % b.capacity]);
        }
    }
    return c;
}
int main(void)
{
    int type;
    int n;

    cout << "Chosse the type, 1 is int and 2 is float:" << endl;
    cin >> type;

    if (type == 1) {
        Queue<int> a(5);
        Queue<int> b(3);
        Queue<int> c(1);
        int value;

        // A queue:
        cout << "A queue: " << endl;
        cout << "Enter the number of elements want to push:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push(value);
        }
        cout << "A Queue size is: " << a.Size() << endl;
        cout << "Capacity is: " << a.Capacity() << endl;
        a.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();
        cout << endl;

        // B queue
        cout << "B queue: " << endl;
        cout << "Enter the number of elements want to push:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            b.Push(value);
        }
        cout << "B Queue size is: " << b.Size() << endl;
        cout << "Capacity is: " << b.Capacity() << endl;
        b.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            b.Pop();
        }

        cout << "B Queue size is: " << b.Size() << endl;
        b.Print();
        cout << endl;


        // C queue:
        cout << "Queue A concat B is:" << endl;
        c = a.Concat(b);
        c.Print();

    } else if (type == 2) {
        Queue<float> a(5);
        Queue<float> b(3);
        Queue<float> c(1);
        float value;

        // A queue:
        cout << "A queue: " << endl;
        cout << "Enter the number of elements want to push:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push(value);
        }
        cout << "A Queue size is: " << a.Size() << endl;
        cout << "Capacity is: " << a.Capacity() << endl;
        a.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();
        cout << endl;


        // B queue
        cout << "B queue: " << endl;
        cout << "Enter the number of elements want to push:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            b.Push(value);
        }
        cout << "B Queue size is: " << b.Size() << endl;
        cout << "Capacity is: " << b.Capacity() << endl;
        b.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            b.Pop();
        }

        cout << "B Queue size is: " << b.Size() << endl;
        b.Print();
        cout << endl;


        // C queue:
        cout << "Queue A concat B is:" << endl;
        c = a.Concat(b);
        c.Print();

    }

    return 0;
}
