#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

struct Offsets
{
    int di, dj;
};

enum directions {N, NE, E, SE, S, SW, W, NW};

Offsets Move[8];

typedef struct {
    int x;
    int y;
    int dir;
} Item;

int maze[14][17];
int mark[14][17];

void Path(const int m, const int p);

int main(void)
{
    char line[18];
    ifstream file;
    file.open("Maze_a.txt");

    if (!file.is_open()) cout << "File fails to open." << endl;
    else {
        for (int i = 0; i < 14; i++) {
            file.getline(line, 18); // get the line in file, file.getline(variable, size). Note that size include \n.
            for (int j = 0; j < 17; j++) {
                maze[i][j] = line[j] - '0';
                mark[i][j] = line[j] - '0';
            }
        }
    }

    file.close();

    cout << "maze :" << endl;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 17; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

    Move[N].di = -1; Move[N].dj = 0;
    Move[NE].di = -1; Move[NE].dj = 1;
    Move[E].di = 0; Move[E].dj = 1;
    Move[SE].di = 1; Move[SE].dj = 1;
    Move[S].di = 1; Move[S].dj = 0;
    Move[SW].di = 1; Move[SW].dj = -1;
    Move[W].di = 0; Move[W].dj = -1;
    Move[NW].di = -1; Move[NW].dj = -1;

    Path(12, 15);
    return 0;
}

void Path(const int m, const int p)
{
    mark[1][1] = 1;
    stack<Item> Stack;
    Item temp;
    temp.x = 1; temp.y = 1; temp.dir = E;
    Stack.push(temp);

    while (!Stack.empty())
    {
        temp = Stack.top();
        Stack.pop();
        int i = temp.x; int j = temp.y; int d = temp.dir;
        while (d < 8)
        {
            int g = i + Move[d].di; int h = j + Move[d].dj;

            if ((!maze[g][h]) && (!mark[g][h])) { // new position
                mark[g][h] = 1;
                temp.x = i; temp.y = j; temp.dir = d + 1;
                Stack.push(temp); // stack it
                i = g; j = h; d = N; // move to (g, h)
            }
            else d++; // try next direction

            if ((g == m) && (h == p)) {
                cout << "Final: (" << m << " " << p << ") " << " <- " << endl; // the Final position;
                // output path
                while (!Stack.empty())
                {
                    if (Stack.size() != 1)
                        cout << " (" << Stack.top().x << ", " << Stack.top().y << ", " << Stack.top().dir - 1
                                     << ") " << " <- " << endl;
                    else
                        cout <<" (" << Stack.top().x << ", " << Stack.top().y << ", " <<  Stack.top().dir - 1
                                    << ") " << ":Beginning" << endl; // the start position
                    Stack.pop();
                }
                return;
            }

        }
    }
    cout << "No path in maze." << endl;
}
