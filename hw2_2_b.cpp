#include <iostream>

using namespace std;

template <class T>
class Bag
{
public:
    Bag(int bagCapacity = 10);
    ~Bag();
    int Size() const;
    bool IsEmpty() const;
    T& Element() const;
    void Push(const T& x);
    void Pop();
    void ChangeSize1D(T*& a, const int oldSize, const int newSize);
protected:
    T *Array;
    int capacity;
    int top;
};

template <class T>
Bag<T>::Bag(int bagCapacity)
:capacity(bagCapacity)
{
    if (capacity < 1)
        throw "Capacity must be > 0";
    Array = new T[capacity];
    top = -1;
}

template <class T>
Bag<T>::~Bag()
{
    delete [] Array;
}

template <class T>
inline int Bag<T>::Size() const
{
    return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const
{
    return (Size() == 0);
}

template <class T>
T& Bag<T>::Element() const
{
    if (IsEmpty())
        throw "It is empty";
    return Array[1];
}

template <class T>
void Bag<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);

    delete [] a;
    a = temp;
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (capacity == top + 1) {
        ChangeSize1D(Array, capacity, capacity * 2);
        capacity *= 2;
    }
    Array[++top] = x;
}

template <class T>
void Bag<T>::Pop( )
{
    if ( IsEmpty() ) throw "Bag is empty, cannot delete";
    int deletePos = top/2;
    copy(Array + deletePos + 1, Array + top + 1, Array + deletePos);
    Array[top--].~T(); // destructor for T
}

template <class T>
class Queue: public Bag<T>
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
    Queue<T> Concat(Queue<T> &b);
private:
    int FRONT;
    int REAR;
};

template <class T>
Queue<T>::Queue(int queueCapacity)
{
    Bag<T>::capacity = queueCapacity;
    FRONT = 0;
    REAR = 0;
    Bag<T>::Array = new T[Bag<T>::capacity];
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
    return Bag<T>::Array[(FRONT + 1) % Bag<T>::capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
    if (IsEmpty()) throw "Queue is empty.";
    return Bag<T>::Array[REAR];
}

template <class T>
void Queue<T>::ChangeCapacity()
{
    T* newQueue = new T[2 * Bag<T>::capacity];

    int start = (FRONT + 1) % Bag<T>::capacity;
    if (start < 2)
        copy(Bag<T>::Array + start, Bag<T>::Array + start + Bag<T>::capacity - 1, newQueue);
    else {
        copy(Bag<T>::Array + start, Bag<T>::Array + Bag<T>::capacity, newQueue);
        copy(Bag<T>::Array, Bag<T>::Array + REAR + 1, newQueue + Bag<T>::capacity - start);
    }

    FRONT = 2 * Bag<T>::capacity - 1;
    REAR = Bag<T>::capacity - 2;
    Bag<T>::capacity *= 2;
    delete [] Bag<T>::Array;
    Bag<T>::Array = newQueue;
}

template <class T>
void Queue<T>::Push(const T& x)
{
    if ((REAR + 1) % Bag<T>::capacity == FRONT) ChangeCapacity();
    REAR = (REAR + 1) % Bag<T>::capacity;
    Bag<T>::Array[REAR] = x;
    Bag<T>::top++;
}

template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    else {
        FRONT = (FRONT + 1) % Bag<T>::capacity;
        Bag<T>::Array[FRONT].~T();
    }
    Bag<T>::top--;
}

template <class T>
void Queue<T>::Print()
{
    int n = 1;
    if (REAR > FRONT)
        for (int i = FRONT + 1; i <= REAR; i++) {
            cout << "Elemant" << " " << n << ":" << Bag<T>::Array[i] << endl;
            n++;
        }
    else if (REAR < FRONT) {
        n = 1;
        for (int i = FRONT + 1; i <= REAR + Bag<T>::capacity; i++) {
            cout << "Elemant" << " " << n << ":" << Bag<T>::Array[i % Bag<T>::capacity] << endl;
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
    else return (REAR + Bag<T>::capacity) - FRONT;
}

int main(void)
{
    int type;
    int n;

    cout << "Chosse the type, 1 is int and 2 is float:" << endl;
    cin >> type;

    if (type == 1) {
        Queue<int> a(5);
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
        a.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();

    } else if (type == 2) {
        Queue<float> a(5);
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
        a.Print();

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();

    }
    return 0;
}
