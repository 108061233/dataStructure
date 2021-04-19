#include <iostream>

using namespace std;

template <class T>
class Deque
{
public:
    Deque (int queueCapacity = 10);
    bool IsEmpty();
    T& Front();
    T& Rear();
    void Push_Rear(const T& x);
    void Push_Front(const T& x);
    void Pop_Rear();
    void Pop_Front();
    void ChangeCapacity();
    void Print();
    int Size();
private:
    int FRONT;
    int REAR;
    int capacity;
    T* QUEUE;
};

template <class T>
Deque<T>::Deque(int queueCapacity)
:capacity(queueCapacity)
{
    FRONT = 0;
    REAR = 0;
    QUEUE = new T[capacity];
}

template <class T>
inline bool Deque<T>::IsEmpty()
{
    return (FRONT == REAR);
}

template <class T>
inline T& Deque<T>::Front()
{
    if (IsEmpty()) throw "Queue is empty.";
    return QUEUE[(FRONT + 1) % capacity];
}

template <class T>
inline T& Deque<T>::Rear()
{
    if (IsEmpty()) throw "Queue is empty.";
    return QUEUE[REAR];
}

template <class T>
void Deque<T>::ChangeCapacity()
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
void Deque<T>::Push_Front(const T& x)
{
    int a;

    if (FRONT == 0) a = capacity - 1;
    else a = FRONT - 1;

    if (a == REAR) ChangeCapacity();

    QUEUE[FRONT] = x;

    if (FRONT == 0) FRONT = capacity - 1;
    else FRONT -= 1;
}

template <class T>
void Deque<T>::Push_Rear(const T& x)
{
    if ((REAR + 1) % capacity == FRONT) ChangeCapacity();
    REAR = (REAR + 1) % capacity;
    QUEUE[REAR] = x;
}

template <class T>
void Deque<T>::Pop_Rear()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    QUEUE[REAR].~T();
    if (REAR == 0) REAR = capacity - 1;
    else REAR--;
}

template <class T>
void Deque<T>::Pop_Front()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    FRONT = (FRONT + 1) % capacity;
    QUEUE[FRONT].~T();
}

template <class T>
void Deque<T>::Print()
{
    int n = 1;
    if (REAR > FRONT)
        for (int i = FRONT + 1; i <= REAR; i++) {
            cout << "Elemant" << " " << n << ":" << QUEUE[i] << endl;
            n++;
        }
    else if (REAR < FRONT) {
        n = 1;
        for (int i = FRONT + 1; i <= REAR + capacity; i++) {
            cout << "Elemant" << " " << n << ":" << QUEUE[i % capacity] << endl;
            n++;
        }
    }
    else cout << "Queue is empty.";
}

template <class T>
int Deque<T>::Size()
{
    if (REAR == FRONT) return 0;
    else if (REAR > FRONT) return REAR - FRONT;
    else return (REAR + capacity) - FRONT;
}

int main(void)
{
    int type;
    int n;

    cout << "Chosse the type, 1 is int and 2 is float:" << endl;
    cin >> type;

    if (type == 1) {
        Deque<float> a(5);
        float value;

        // A queue:
        cout << "A queue: " << endl;

        // Push from REAR
        cout << "Enter the number of elements want to push from rear:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push_Rear(value);
        }
        a.Print();

        // Push from FRONT
        cout << "Enter the number of elements want to push from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push_Front(value);
        }
        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();

        // Pop from FRONT
        cout << "Enter the number of elements want to pop from front: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop_Front();
        }
        a.Print();

        // Pop from REAR
        cout << "Enter the number of elements want to pop from rear: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop_Rear();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();

    } else if (type == 2) {
        Deque<float> a(5);
        float value;

        // A queue:
        cout << "A queue: " << endl;

        // Push from REAR
        cout << "Enter the number of elements want to push from rear:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push_Rear(value);
        }
        a.Print();

        // Push from FRONT
        cout << "Enter the number of elements want to push from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Push value:";
            cin >> value;
            a.Push_Front(value);
        }
        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();

        // Pop from FRONT
        cout << "Enter the number of elements want to pop from front: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop_Front();
        }
        a.Print();

        // Pop from REAR
        cout << "Enter the number of elements want to pop from rear: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop_Rear();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        a.Print();
    }

    return 0;
}
