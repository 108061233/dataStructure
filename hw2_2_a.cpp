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
    return Array[0];
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
class Stack: public Bag<T>
{
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    T& Top() const;
    void Pop();
};

template <class T>
Stack<T>::Stack(int stackCapacity)
{
    Bag<T>::capacity = stackCapacity;
    if (Bag<T>::capacity < 1)
        throw "Capacity must be > 0";
    Bag<T>::Array = new T[Bag<T>::capacity];
    Bag<T>::top = -1;
}

template <class T>
Stack<T>::~Stack()
{
    delete [] Bag<T>::Array;
}

template <class T>
T& Stack<T>::Top() const
{
    if (Bag<T>::IsEmpty()) throw "Stack is empty.";
    return Bag<T>::Array[Bag<T>::top];
}

template <class T>
void Stack<T>::Pop()
{
    if(Bag<T>::IsEmpty()) throw "Stack is empty, cannot delete.";
    Bag<T>::Array[Bag<T>::top--].~T();
}

int main(void)
{
    int type;
    int n;

    cout << "Chosse the type, 1 is int and 2 is float:" << endl;
    cin >> type;

    if (type == 1) {
        Stack<int> a(5);
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
        cout << "A stack size is: " << a.Size() << endl;
        cout << "Top of A is: " << a.Top() << endl;

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A stack size is: " << a.Size() << endl;
        cout << "Top of A is: " << a.Top() << endl;

    } else if (type == 2) {
        Stack<float> a(5);
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
        cout << "Top of A is: " << a.Top() << endl;

        cout << "Enter the number of elements want to pop: " << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.Pop();
        }

        cout << "A Queue size is: " << a.Size() << endl;
        cout << "Top of A is: " << a.Top() << endl;

    }

    return 0;
}
