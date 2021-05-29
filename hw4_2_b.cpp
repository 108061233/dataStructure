#include <iostream>

using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}  // virtual destructor
    virtual bool IsEmpty() const = 0; //return true iff empty
    virtual const T& Top() const = 0; //return reference to the max
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T>
{
public:
    MinHeap(int theCapacity = 10);  // constructor
    bool IsEmpty() const; //return true iff empty
    const T& Top() const {return heap[1];} //return reference to the max
    void ChangeSize1D(T*& a, const int oldSize, const int newSize);
    void Push(const T& e);
    void Pop();
    void Print();
private:
    T* heap;      // element array
    int heapSize; // number of elements in heap
    int capacity; // size of the element array
};

template <class T>
MinHeap<T>::MinHeap(int theCapacity) // constructor
{
    if(theCapacity < 1) throw "Capacity must be >= 1";
    capacity = theCapacity;
    heapSize = 0;
    heap = new T [capacity + 1]; // heap[0] unused
}

template <class T>
bool MinHeap<T>::IsEmpty() const
{
    if (heapSize == 0) return true;
    else return false;
}

template <class T>
void MinHeap<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);

    delete [] a;
    a = temp;
}

template <class T>
void MinHeap<T>::Push(const T& e)
{ // add element e to max heap
    if (heapSize + 1 == capacity) { // double the capacity
        ChangeSize1D(heap, capacity, 2*capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode/2] > e)
    { // bubbling up
        heap[currentNode] = heap[currentNode/2];//move parent down
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MinHeap<T>::Pop()
{ // Delete max element
    if (IsEmpty ()) throw "Heap is empty. Cannot delete.";
    heap[1].~T(); // delete max element
    T lastE = heap[heapSize--];  // remove last element from heap
    // trickle down to find a position to place the last element
    int currentNode = 1; // root
    int child = 2;       //  a child of current node
    while (child <= heapSize){
        // set child to larger child of currentNode
        if (child < heapSize && heap[child] > heap[child + 1]) child++;

        if (lastE <= heap[child]) break;
        heap[currentNode] = heap[child]; // move child up
        currentNode = child; child *= 2; // move down a level
    }
    heap[currentNode] = lastE;
}

template <class T>
void MinHeap<T>::Print()
{
    if (IsEmpty())
        cout << "Min Heap is empty";
    else {
        cout << "Min Heap: ";
        for (int i = 1; i <= heapSize; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
}

int main(void)
{
    MinHeap<int> a;
    int n, value;
    cout << "Enter the number of elements want to push: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the value: ";
        cin >> value;
        a.Push(value);
    }
    cout << "Min value is: " << a.Top() << endl;
    a.Print();

    cout << "Enter the number of elements want to pop: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Pop " << i + 1 << endl;
        a.Pop();
        a.Print();
    }
}
