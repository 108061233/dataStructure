#include <iostream>

using namespace std;

class MatrixWDigraph{
public:
    MatrixWDigraph(int k);
    void Setup();
    void Dijkstra(int v);
    void BellmanFord(int v);
    void Floyd();
    void Print();
private:
    int n;
    int e;
    bool *s;
    int *p;
    double **length;
    double **a;
    double *dist;
};

MatrixWDigraph::MatrixWDigraph(int k)
{
    e = 0;
    n = k;
    s = new bool[n];
    p = new int[n];
    length = new double *[n];
    a = new double *[n];
    for (int i = 0; i < n; i++) {
        length[i] = new double[n];
        a[i] = new double[n];
    }
    dist = new double[n];
}

void MatrixWDigraph::Setup()
{
    int v1, v2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) length[i][j] = 0;
            else length[i][j] = 50000;
        }
    }

    cout << "Enter the number of edges: ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        cout << "Enter " << i + 1 << " edge" << endl;
        cout << "Enter the vertex of start: ";
        cin >> v1;
        cout << "Enter the vertex of end: ";
        cin >> v2;

        cout << "Enter the weight of edge: ";
        cin >> length[v1][v2];
    }
}

void MatrixWDigraph::Print()
{
    cout << "Graph is" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cout << "<" << i << ", " << j << ">";
            cout << ", weight: " << length[i][j] << endl;
        }
}
void MatrixWDigraph::Dijkstra(int v)
{
    for (int i = 0; i < n ; i++) { // initialization
        s[i] = false;              // the set, S
        dist[i] = length[v][i]; // dist[]
        if (length[v][i] != 50000) p[i] = v;
        else p[i] = -1;
    }
    p[v] = -1;

    cout << "Iteration, Vertex selected, Distance" << endl;
    cout << "Initial " << "select: none";
    for (int i = 0; i < n; i++) {
       cout << " [" << i << "]: " << dist[i];
    }
    cout << endl;

    int u;
    s[v] = true;
    dist[v] = 0;
    for (int i = 0; i < n-1 ; i++) { // n-1 shortest paths from v
        for (int j = 0; j < n; j++)
            if (!s[j]) {
                u = j;
                break;
            }

        for (int j = 0; j < n; j++)
            if (!s[j] && j != v)
                if (dist[j] < dist[u]) u = j;

        s[u] = true;  // u becomes a member of S
        for (int w = 0; w < n; w++) // update dist[w]
            if (!s[w] && (dist[u] + length[u][w]) < dist[w]) {
                dist[w] = dist[u] + length[u][w];
                p[w] = u;
            }

        cout << i + 1 << " iteration " << "select: " << u;
        for (int j = 0; j < n; j++) {
            cout << " [" << j << "]: " << dist[j];
        }
        cout << endl;

    }

    cout << "Shortest paths: " << endl;

    for (int i = 0; i < n; i++) {
        if (i != v) {
            int cur = i;
            while (cur != -1) {
                if (cur != v) cout << cur << " <- ";
                else cout << cur;
                cur = p[cur];
            }
            cout << ", Length: " << dist[i];
        }
        if (i != v) cout << endl;
    }
}

void MatrixWDigraph::BellmanFord(int v)
{ // n is the number of vertices
  // in-place update for dist[] is used
    for (int i = 0; i < n ; i++)
        dist[i] = length[v][i]; // dist1[] initialization

    cout << "k = 1, ";
    for (int i = 0; i < n; i++) {
       cout << " [" << i << "]: " << dist[i];
    }
    cout << endl;

    double change[n];
    for (int i = 0; i < n; i++) change[i] = 50000;

    for (int k = 2; k <= n-1; k++) {// dist2 ~ dist(n-1)
        for (int u = 0; u < n; u++)
            if (u != v)
                for (int i = 0; i < n; i++)
                    if (i != u)
                        if (change[u] > dist[i] + length[i][u])
                            change[u] = dist[i] + length[i][u];

        for (int i = 0; i < n; i++)
            if (change[i] != 50000) {
                dist[i] = change[i];
                change[i] = 50000;
            }

        cout << "k = " << k << ", ";
        for (int i = 0; i < n; i++) {
            cout << " [" << i << "]: " << dist[i];
        }
        cout << endl;
    }
}

void MatrixWDigraph::Floyd()
{
    for (int i = 0; i<n; i++)
        for (int j = 0; j<n; j++)
            a[i][j]= length[i][j];

    cout << "A(-1): " << endl;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    for (int k= 0; k<n; k++) {
        for (int i= 0; i<n; i++)
            for (int j= 0; j<n; j++)
                if(a[i][j] > (a[i][k] + a[k][j]))
                    a[i][j] = a[i][k] + a[k][j];

        cout << "A(" << k << "): " << endl;
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++)
                cout << a[i][j] << " ";
            cout << endl;
        }
    }
}

int main()
{
    int n, m, v;
    cout << "Enter the number of vertices: ";
    cin >> n;
    MatrixWDigraph g1(n);
    cout << "Set the graph" << endl;
    g1.Setup();
    cout << endl;
    g1.Print();
    cout << "Choose the shortest path method (1 is Dijkstra, 2 is Bellman-Ford, 3 is Floyd): ";
    cin >> m;

    if (m == 1) {
        cout << "The result of Dijkstra: " << endl;
        cout << "Enter the start vertex: ";
        cin >> v;
        g1.Dijkstra(v) ;
    } else if (m == 2) {
        cout << "The result of Bellman-Ford: " << endl;
        cout << "Enter the start vertex: ";
        cin >> v;
        g1.BellmanFord(v);
    } else if (m == 3) {
        cout << "The result of Floyd: " << endl;
        g1.Floyd() ;
    }

}
