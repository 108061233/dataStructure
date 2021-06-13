#include <iostream>
#include "Queue.cpp"

using namespace std;

class linkedGraph;

template <class T>
class ChainNode{
friend class LinkedGraph;
public:
    ChainNode() {link = 0;}
    ChainNode(T& a, ChainNode<T> *b)
    {
        data = a;
        link = b;
    }
private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class Chain{
friend class LinkedGraph;
public:
    Chain() {first = 0;}
//Chain manipulations
private:
    ChainNode<T>* first;
};

class LinkedGraph
{
public:
    LinkedGraph(const int vertices = 0)
    : n(vertices), e(0)
    {
        adjLists = new Chain<int>[n];
    }

    void Setup();
    void BFS(int v);

    void DFS(int v);
    void DFS(int v, int u);
    void Component();

    void DfnLow(int v);
    void DfnLow(int u, int v);
private:
    Chain<int> *adjLists;
    int n, e;
    bool *visited;
    int num;
    int *dfn;
    int *low;
};

void LinkedGraph::Setup()
{
    int v1, d, v2;
    ChainNode<int> *curNode;

    for (int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << " vertex: ";
        cin >> v1;
        cout << "Enter the degree of vertex: ";
        cin >> d;
        for (int j = 0; j < d; j++) {
            if (j == 0) {
                cout << "Enter the connect vertex: ";
                cin >> v2;
                adjLists[i].first = new ChainNode<int> (v2, 0);
                curNode = adjLists[i].first;
                e++;
            } else {
                cout << "Enter the connect vertex: ";
                cin >> v2;
                curNode->link = new ChainNode<int> (v2, 0);
                curNode = curNode->link;
                e++;
            }
        }
    }
    e /= 2;
}

void LinkedGraph::DFS(int v)
{
  visited = new bool[n];
  fill (visited, visited + n, false);
  DFS(v, 0); // start search at vertex 0
  delete [] visited;
}

void LinkedGraph::DFS(int v, int u)
// visit all previously unvisited vertices that are
// reachable from vertex @v@
{
    visited[v] = true;  cout << v << " ";

    if (! adjLists[v].first) return;
    ChainNode<int> *curNode = adjLists[v].first;
    int w = curNode->data;

    while (1)
    {
        if (! visited[w]) DFS(w, 0);
        if (curNode->link != 0) {
            curNode = curNode->link;
            w = curNode->data;
        } else return;
    }
}

void LinkedGraph::BFS(int v)
{//BFS(v), visited[i]=true when visited
    int w;
    visited = new bool [n];
    fill (visited, visited + n, false);
    visited[v] = true;
    Queue<int> q;
    q.Push(v);

    while (!q.IsEmpty()) {
        v = q.Front();
        q.Pop();
        cout << v << " ";

        ChainNode<int> *curNode = adjLists[v].first;
        if (curNode != 0) w = curNode->data;

        while (curNode != 0) {
            if (!visited[w]) {
                q.Push(w);
                visited[w] = true;
            }
            curNode = curNode->link;
            if (curNode != 0) w = curNode->data;
        }
    } // end of while loop
    delete [] visited;
}

void LinkedGraph::Component()
{
    int number = 1;
    visited = new bool [n];
    fill (visited, visited + n, false);
    for (int i = 0 ; i < n ; i++){
        if (!visited[i]) {
            cout << "The " << number << " component: ";
            DFS(i, 0); // find the component containing i
            cout << endl;
            number++;
        }
    }
    delete [] visited;
}

void LinkedGraph::DfnLow(int v)
{
    num = 1;
    dfn = new int[n];
    low = new int[n];
    fill(dfn, dfn + n, 0);
    fill(low, low + n, 0);
    DfnLow(v, -1);

    for (int i = 0; i < n; i++) {
        if (dfn[i] != 0) {
            cout << "Vertex: " << i;
            cout << " dfn: " << dfn[i];
            cout << " low: " << low[i] << endl;
        }
    }
    delete [] dfn;
    delete [] low;
}

void LinkedGraph::DfnLow(int u, int v)
{
    int w;

    dfn[u] = low[u] = num++;

    ChainNode<int> *curNode = adjLists[u].first;
    if (curNode != 0) w = curNode->data;

    while (curNode != 0) {
        if (dfn[w] == 0) {
            DfnLow(w, u);
            low[u] = min(low[u], low[w]);
        } else if (w != v) low[u] = min(low[u], dfn[w]);
        curNode = curNode->link;
        if (curNode != 0) w = curNode->data;
    }
}

int main()
{
    int v;
    cout << "Enter the number of vertices: ";
    cin >> v;
    LinkedGraph g1(v);

    cout << "Set the graph" << endl;
    g1.Setup();
    cout << endl;

    cout << "DFS of vertex 0: ";
    g1.DFS(0);
    cout << endl;

    cout << "BFS of vertex 0: ";
    g1.BFS(0);
    cout << endl;

    cout << "DfnLow of vertex 0: " << endl;
    g1.DfnLow(0);
    cout << endl;

    cout << "DFS of vertex 3: ";
    g1.DFS(3);
    cout << endl;

    cout << "BFS of vertex 3: ";
    g1.BFS(3);
    cout << endl;

    cout << "DfnLow of vertex 3: " << endl;
    g1.DfnLow(3);
    cout << endl;

    cout << "DFS of vertex 7: ";
    g1.DFS(7);
    cout << endl;

    cout << "BFS of vertex 7: ";
    g1.BFS(7);
    cout << endl;

    cout << "DfnLow of vertex 7: " << endl;
    g1.DfnLow(7);
    cout << endl;

    cout << "Components: " << endl;
    g1.Component();
}


