#include<iostream>

using namespace std;

template <class T> class List;
template <class T> ostream& operator<< (ostream& os, List<T>& a);

template <class T>
class Node{
friend class List<T>;
friend ostream& operator<< <>(ostream& os, List<T>& a);
public:
    Node(T& a, Node<T> *b)
    {
        data = a;
        link = b;
    }
private:
    T data;
    Node<T> *link;
};

template <class T>
class List{
public:
    List() {first = 0;}
    ~List();
    void InsertFront(T e);
    void DeleteFront();
    void DeleteBack();
    T Front();
    T Back();
    void Delete(int i);
    void Insert(int i, T e);
    T Get(int i);
    friend ostream& operator<< <>(ostream& os, List<T>& a);

    class Iterator{
    public:
        //typedefs required by C++ for a forward iterator
        //Constructor
        Iterator(Node<T>* startNode = 0) {current = startNode;}
        //Dereferencing operators
        T& operator *() const {return current -> data;}
        T* operator ->() const {return &current -> data;}
        //Increment
        Iterator& operator ++() //preincrement
        {
            current = current ->link;
            return *this;
        }

        Iterator& operator ++(int) //postincrement
        {
            Iterator old = *this;
            current = current ->link; return old;
        }

        //Equality test
        bool operator!=(const Iterator r) {return current != r.current;}
        bool operator==(const Iterator r) {return current == r.current;}

        private:
            Node<T> *current;
        };
    Iterator Begin() {return Iterator(first);}
    Iterator End() {return Iterator(0);}

private:
    Node<T>* first;
};

template<class T>
List<T>::~List<T>()
{
    Node<T> *delNode;
    while(first) {
        delNode = first;
        first = first -> link;
        delete delNode;
    }
}

template<class T>
void List<T>::InsertFront(T e)
{
    if (!first) first = new Node<T>(e, 0);
    else first = new Node<T> (e, first);
}

template<class T>
void List<T>::DeleteFront()
{
    if (!first) throw "List is empty";
    Node<T> *delNode = first;
    first = first -> link;
    delete delNode;
}

template<class T>
void List<T>::DeleteBack()
{
    if (!first) throw "List is empty";
    Node<T> *lastNode = first;
    Node<T> *beforeNode = 0;
    while (lastNode -> link != 0) {
        if (lastNode -> link -> link == 0) beforeNode = lastNode;
        lastNode = lastNode -> link;
    }
    beforeNode -> link = 0;
    delete lastNode;
}

template<class T>
T List<T>::Front()
{
    if (!first) throw "List is empty";
    return first -> data;
}

template<class T>
T List<T>::Back()
{
    if (!first) throw "List is empty";
    Node<T> *lastNode = first;
    while (lastNode -> link != 0)
        lastNode = lastNode -> link;

    return lastNode -> data;
}

template<class T>
T List<T>::Get(int i)
{
    if (!first) throw "List is empty";
    Node<T> *currentNode = first;
    for (int n = 0; n < i; n++) {
        currentNode = currentNode -> link;
        if (!currentNode) throw "Node does not exist";
    }

    return currentNode -> data;
}

template<class T>
void List<T>::Delete(int i)
{
    if (!first) throw "List is empty";

    Node<T> *currentNode = first;
    Node<T> *beforeNode = first;

    if (i == 0) {
        first = first -> link;
        delete currentNode;
    } else {
        for (int n = 0; n < i - 1; n++) {
            beforeNode = beforeNode -> link;
            if (!beforeNode || beforeNode -> link == 0) throw "Node does not exist";
        }
        currentNode = beforeNode -> link;
        beforeNode -> link = currentNode -> link;
        delete currentNode;
    }
}

template<class T>
void List<T>::Insert(int i,T e)
{
    Node<T> *currentNode = first;
    Node<T> *beforeNode = first;

    if (i == 0)
        first = new Node<T>(e, first);
    else {
        for (int n = 0; n < i - 1; n++) {
            beforeNode = beforeNode -> link;
            if (!beforeNode) throw "Node can not insert";
        }

        currentNode = beforeNode -> link;
        beforeNode -> link = new Node<T>(e, currentNode);
    }
}

template<class T>
ostream& operator<<(ostream& os, List<T>& a)
{
    Node<T> *currentNode = a.first;
    int n = 0;
    while (currentNode) {
        currentNode = currentNode -> link;
        n++;
    }

    if (n == 0) os << "List is empty";
    else
        for (int i = 0; i < n; i++)
            os << "Node " << i << ": " << a.Get(i) << endl;
}

int main(void)
{
    int type;
    int n;

    cout << "Chosse the type, 1 is int and 2 is float:" << endl;
    cin >> type;

    if (type == 1) {
        List<int> a;
        int value;

        cout << "Enter the number of nodes want to insert from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter value:";
            cin >> value;
            a.InsertFront(value);
        }
        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the index you want to get: " << endl;
        cin >> n;
        cout << a.Get(n) << endl;

        cout << "Enter the index you want to insert: " << endl;
        cin >> n;
        cout << "Enter value:";
        cin >> value;
        a.Insert(n, value);
        cout << a;

        cout << "Enter the number of nodes want to delete from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.DeleteFront();
        }
        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the number of nodes want to delete from back:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.DeleteBack();
        }

        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the index you want to delete: " << endl;
        cin >> n;
        a.Delete(n);
        cout << a;

        cout << "Test Iterator:" << endl;

        int j = 0;
        for (List<int>::Iterator i = a.Begin(); i != a.End(); i++) {
            cout << "Node " << j << " data is " << *i << endl;
            j++;
        }

        cout << "Test destructor:" << endl;
        a.~List();
        cout << a;

    } else if (type == 2) {
        List<float> a;
        float value;

        cout << "Enter the number of nodes want to insert from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter value:";
            cin >> value;
            a.InsertFront(value);
        }
        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the index you want to get: " << endl;
        cin >> n;
        cout << a.Get(n) << endl;

        cout << "Enter the index you want to insert: " << endl;
        cin >> n;
        cout << "Enter value:";
        cin >> value;
        a.Insert(n, value);
        cout << a;

        cout << "Enter the number of nodes want to delete from front:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.DeleteFront();
        }
        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the number of nodes want to delete from back:" << endl;
        cin >> n;

        for (int i = 0; i < n; i++) {
            a.DeleteBack();
        }

        cout << a;
        cout << "Front: " << a.Front() << " ";
        cout << "Back: " << a.Back() << endl;

        cout << "Enter the index you want to delete: " << endl;
        cin >> n;
        a.Delete(n);
        cout << a;

        cout << "Test Iterator:" << endl;

        int j = 0;
        for (List<float>::Iterator i = a.Begin(); i != a.End(); i++) {
            cout << "Node " << j << " data is " << *i << endl;
            j++;
        }

        cout << "Test destructor:" << endl;
        a.~List();
        cout << a;

    }
    return 0;
}


