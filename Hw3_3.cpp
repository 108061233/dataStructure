#include<iostream>

using namespace std;

struct Triple{int row, col, value;};

class Matrix;

class MatrixNode {
friend class Matrix;
friend istream& operator>>(istream& is, Matrix& matrix);
friend ostream& operator<<(ostream& os, Matrix& a);
private:
    MatrixNode *down , *right;
    bool head;
    union {
        MatrixNode *next;
        Triple triple;
    };
    MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple *t)
{
    head = b;
    if (b) {
        right = down = this;
        next = 0;
    }
    else triple = *t;
}

class Matrix{
friend istream& operator>>(istream& is, Matrix& matrix);
friend ostream& operator<<(ostream& os, Matrix& a);
public:
    Matrix() {headnode = 0;}
    Matrix (const Matrix& b);
    ~Matrix();
    Matrix operator+(const Matrix& b);
    Matrix operator*(Matrix& b);
    Matrix Transpose();
private:
    MatrixNode *headnode;
};

Matrix::Matrix(const Matrix& b)
{
    int B = 0;
    Triple s;
    Triple temp;
    s.row = b.headnode->triple.row; s.col = b.headnode->triple.col; s.value = b.headnode->triple.value;
    headnode = new MatrixNode(false, &s);
    int p = max(s.row, s.col);

    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);

    MatrixNode *BNode = b.headnode -> right -> down;
    while (BNode->head) {
        BNode = BNode -> next;
        BNode = BNode -> right;
    }

    MatrixNode *last = head[0];

    while (B < b.headnode->triple.value) {
        temp.row = BNode->triple.row; temp.col = BNode->triple.col; temp.value = BNode->triple.value;
        last = last->right = new MatrixNode(false, &temp);

        if (head[temp.col] -> next == 0) {
            head[temp.col] -> right = last;
            head[temp.col] -> next = last;
        } else {
            head[temp.col]->next->right = last;
            head[temp.col]->next = last;
        }

        BNode = BNode->right;
        B++;
        if (BNode->head) {
            last->right = head[temp.row++];
            if (temp.row < p)
                last = head[temp.row];
            while (BNode->head && B < b.headnode->triple.value) {
                BNode = BNode->next;
                BNode = BNode->right;
            }
        }
    }

    for (int i = 0; i < s.col; i++)
        if (head[i]->next != 0)
            head[i]->next->down = head[i]; // close all column lists

    // link the header nodes together

    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = headnode;
    headnode->right = head[0];
    delete [] head;
}

Matrix::~Matrix()
{// Return all nodes to the av list, which is a chain linked
 // via the right field.
 // av is a static variable pointing to the first of the av list.
    if (!headnode)
        return; // no nodes to delete
    MatrixNode *x = headnode->right;
    MatrixNode *temp = 0;

    while (x != headnode) { // return nodes by rows
        MatrixNode *y = x->right;
        while (y != x) {
            temp = y;
            y = y->right;
            delete temp;
        }
        x = x->next; // next row
    }
    headnode = 0;
}

istream& operator>>(istream& is, Matrix& matrix)
{// Read in a maxtix and set up its linked representation
    Triple s;
    cout << "Enter matrix rows, cols, and terms:";
    is >> s.row >> s.col >> s.value; // matrix dimensions
    int p = max(s.row, s.col);
    // set up header node for list of  header nodes
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
        return is;  // for supporting "cin >> mi >> mj;"
    }
    // at least one row or column
    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    int currentRow = 0;

    MatrixNode *last = head[0]; // last node in current row
    for (int i = 0; i < s.value; i++)   // input triples
    {
        Triple t;
        cout << "Enter row, col, and value:";
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) { // end of current row
            last->right = head[currentRow]; // close current row
            currentRow = t.row;
            last = head[currentRow];
        } // end of if

        last = last->right = new MatrixNode(false, &t);
        // link new node into row list

        // different
        if (head[t.col] -> next == 0) {
            head[t.col] -> down = last;
            head[t.col] -> next = last;
        } else {
            head[t.col]->next->down = last;
            head[t.col]->next = last;
        }
        //

        // link into column list
    } // end of for

    last->right = head[currentRow]; // close last row

    // different
    for (int i = 0; i < s.col; i++)
        if (head[i]->next != 0)
            head[i]->next->down = head[i]; // close all column lists
    // different

    // link the header nodes together
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
    delete [] head;
    return is;
}

ostream& operator<<(ostream& os, Matrix& a)
{
    if (a.headnode == 0) os << "Matrix does not exist." << endl;
    else {
        cout << "Matrix is: " << endl;
        MatrixNode *currentNode = a.headnode -> right;
        while (currentNode->right->head) currentNode = currentNode->next;
        currentNode = currentNode->right;

        for (int i = 0; i < a.headnode->triple.value;) {
            cout << "(" << currentNode->triple.row << ", ";
            cout << currentNode->triple.col << ", ";
            cout << currentNode->triple.value << ")" << endl;
            currentNode = currentNode -> right;
            i++;
            while (currentNode->head && i < a.headnode->triple.value) {
                currentNode = currentNode -> next;
                currentNode = currentNode -> right;
            }
        }
    }
}

Matrix Matrix::operator+(const Matrix& b)
{
    int A = 0, B = 0, n = 0;
    Triple s;
    Triple temp;
    s.row = headnode->triple.row; s.col = headnode->triple.col; s.value = 0;
    Matrix c;
    c.headnode = new MatrixNode(false, &s);
    int p = max(s.row, s.col);

    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);

    MatrixNode *ANode = headnode -> right -> right;
    MatrixNode *BNode = b.headnode -> right -> right;
    MatrixNode *last = head[0];

    while (A < headnode->triple.value && B < b.headnode->triple.value) {
        if (ANode->head)
            ANode = ANode->next->right;
        else if (BNode->head)
            BNode = BNode->next->right;
        else
            if (ANode->triple.row < BNode->triple.row) {
                temp.col = ANode->triple.col; temp.row = ANode->triple.row; temp.value = ANode->triple.value;
                last = last->right = new MatrixNode(false, &temp);

                if (head[temp.col] -> next == 0) {
                    head[temp.col] -> down = last;
                    head[temp.col] -> next = last;
                } else {
                    head[temp.col]->next->down = last;
                    head[temp.col]->next = last;
                }
                ANode = ANode->right;
                if (ANode->head) {
                    last->right = head[temp.row++];
                    if (temp.row < p)
                        last = head[temp.row];
                }
                A++;
                n++;
            } else if (ANode->triple.row > BNode->triple.row) {
                temp.col = BNode->triple.col; temp.row = BNode->triple.row; temp.value = BNode->triple.value;
                last = last->right = new MatrixNode(false, &temp);

                if (head[temp.col] -> next == 0) {
                    head[temp.col] -> down = last;
                    head[temp.col] -> next = last;
                } else {
                    head[temp.col]->next->down = last;
                    head[temp.col]->next = last;
                }

                BNode = BNode->right;
                if (BNode->head) {
                    last->right = head[temp.row++];
                    if (temp.row < p)
                        last = head[temp.row];
                }
                B++;
                n++;
            } else
                if (ANode->triple.col < BNode->triple.col) {
                    temp.col = ANode->triple.col; temp.row = ANode->triple.row; temp.value = ANode->triple.value;
                    last = last->right = new MatrixNode(false, &temp);

                    if (head[temp.col] -> next == 0) {
                        head[temp.col] -> down = last;
                        head[temp.col] -> next = last;
                    } else {
                        head[temp.col]->next->down = last;
                        head[temp.col]->next = last;
                    }

                    ANode = ANode->right;
                    A++;
                    n++;
                } else if (ANode->triple.col > BNode->triple.col){
                    temp.col = BNode->triple.col; temp.row = BNode->triple.row; temp.value = BNode->triple.value;
                    last = last->right = new MatrixNode(false, &temp);

                    if (head[temp.col] -> next == 0) {
                        head[temp.col] -> down = last;
                        head[temp.col] -> next = last;
                    } else {
                        head[temp.col]->next->down = last;
                        head[temp.col]->next = last;
                    }

                    BNode = BNode->right;
                    B++;
                    n++;
                } else {
                    temp.col = ANode->triple.col; temp.row = ANode->triple.row; temp.value = ANode->triple.value + BNode->triple.value;
                    if (!temp.value) {
                        ANode = ANode->right;
                        BNode = BNode->right;
                        A++;
                        B++;
                    } else {
                        last = last->right = new MatrixNode(false, &temp);

                        if (head[temp.col] -> next == 0) {
                            head[temp.col] -> down = last;
                            head[temp.col] -> next = last;
                        } else {
                            head[temp.col]->next->down = last;
                            head[temp.col]->next = last;
                        }
                        ANode = ANode->right;
                        BNode = BNode->right;
                        A++;
                        B++;
                        n++;

                        if (ANode->head && BNode->head) {
                            last->right = head[temp.row++];
                            if (temp.row < p)
                                last = head[temp.row];
                        }
                    }
                }
    }
    while (A < headnode->triple.value) {
        temp.col = ANode->triple.col; temp.row = ANode->triple.row; temp.value = ANode->triple.value;
        last = last->right = new MatrixNode(false, &temp);

        if (head[temp.col] -> next == 0) {
            head[temp.col] -> down = last;
            head[temp.col] -> next = last;
        } else {
            head[temp.col]->next->down = last;
            head[temp.col]->next = last;
        }

        ANode = ANode->right;
        if (ANode->head) {
            last->right = head[temp.row++];
            if (temp.row < p)
                last = head[temp.row];
            while (ANode->head) {
                ANode = ANode->next;
                ANode = ANode->right;
            }
        }
        A++;
        n++;
    }

    while (B < b.headnode->triple.value) {
        temp.col = BNode->triple.col; temp.row = BNode->triple.row; temp.value = BNode->triple.value;
        last = last->right = new MatrixNode(false, &temp);

        if (head[temp.col] -> next == 0) {
            head[temp.col] -> down = last;
            head[temp.col] -> next = last;
        } else {
            head[temp.col]->next->down = last;
            head[temp.col]->next = last;
        }

        BNode = BNode->right;
        if (BNode->head) {
            last->right = head[temp.row++];
            if (temp.row < p)
                last = head[temp.row];
            while (BNode->head) {
                BNode = BNode->next;
                BNode = BNode->right;
            }
        }
        B++;
        n++;
    }

    c.headnode->triple.value = n;
    for (int i = 0; i < s.col; i++)
        if (head[i]->next != 0)
            head[i]->next->down = head[i]; // close all column lists

    // link the header nodes together

    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = c.headnode;
    c.headnode->right = head[0];
    delete [] head;
    return c;
}

Matrix Matrix::Transpose()
{
    int A = 0;
    Triple s;
    Triple temp;
    s.row = headnode->triple.col; s.col = headnode->triple.row; s.value = headnode->triple.value;
    Matrix c;
    c.headnode = new MatrixNode(false, &s);
    int p = max(s.row, s.col);

    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);

    MatrixNode *ANode = headnode -> right -> down;
    while (ANode->head) {
        ANode = ANode -> next;
        ANode = ANode -> down;
    }

    MatrixNode *last = head[0];

    while (A < headnode->triple.value) {
        temp.col = ANode->triple.row; temp.row = ANode->triple.col; temp.value = ANode->triple.value;
        last = last->right = new MatrixNode(false, &temp);

        if (head[temp.col] -> next == 0) {
            head[temp.col] -> down = last;
            head[temp.col] -> next = last;
        } else {
            head[temp.col]->next->down = last;
            head[temp.col]->next = last;
        }

        ANode = ANode->down;
        A++;
        if (ANode->head) {
            last->right = head[temp.row++];
            if (temp.row < p)
                last = head[temp.row];
            while (ANode->head && A < headnode->triple.value) {
                ANode = ANode->next;
                ANode = ANode->down;
            }
        }
    }

    for (int i = 0; i < s.col; i++)
        if (head[i]->next != 0)
            head[i]->next->down = head[i]; // close all column lists

    // link the header nodes together

    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = c.headnode;
    c.headnode->right = head[0];
    delete [] head;
    return c;
}

Matrix Matrix::operator*(Matrix& b)
{
    int A = 0, B = 0, n = 0, sum = 0;
    Triple s;
    Triple temp;
    s.row = headnode->triple.row; s.col = b.headnode->triple.col; s.value = 0;
    Matrix c;
    c.headnode = new MatrixNode(false, &s);
    int p = max(s.row, s.col);

    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);

    Matrix b_T(b.Transpose());

    MatrixNode *ANode = headnode -> right;
    MatrixNode *last = head[0];

    while (A < headnode->triple.row) {
        if (ANode->right->head)
            while (ANode->right->head && A < headnode->triple.row) {
                ANode = ANode->next;
                A++;
            }
        else {
            MatrixNode *BNode = b_T.headnode -> right -> right;
            B = 0;
            while (B < b_T.headnode->triple.row) {
                if (BNode->head)
                    while (BNode->head && B < b_T.headnode->triple.row) {
                        BNode = BNode->next->right;
                        B++;
                    }
                else {
                    sum = 0;
                    MatrixNode *curA = ANode->right;
                    while (!BNode->head || !curA->head)
                        if (curA->head || (!BNode->head && BNode->triple.col < curA->triple.col))
                            BNode = BNode->right;
                        else if (BNode->head || (!curA->head && BNode->triple.col > curA->triple.col))
                            curA = curA->right;
                        else {
                            sum += BNode->triple.value * curA->triple.value;
                            curA = curA->right;
                            BNode = BNode->right;
                        }

                    if (!sum) {
                        B++;
                        if (B < b_T.headnode->triple.row)
                            BNode = BNode->next->right;
                    } else {
                        temp.row = A; temp.col = B; temp.value = sum;
                        last = last->right = new MatrixNode(false, &temp);

                        if (head[temp.col] -> next == 0) {
                            head[temp.col] -> down = last;
                            head[temp.col] -> next = last;
                        } else {
                            head[temp.col]->next->down = last;
                            head[temp.col]->next = last;
                        }

                        BNode = BNode->next->right;
                        B++;
                        n++;
                    }
                }
            }
            last->right = head[A++];
            if (A < p)
                last = head[A];

            ANode = ANode->next;
        }
    }

    c.headnode->triple.value = n;
    for (int i = 0; i < s.col; i++)
        if (head[i]->next != 0)
            head[i]->next->down = head[i]; // close all column lists

    // link the header nodes together

    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p-1]->next = c.headnode;
    c.headnode->right = head[0];

    delete [] head;
    return c;
}

int main(void)
{
    Matrix a;
    Matrix b;
    cin >> a;
    cout << a;
    cin >> b;
    cout << b;

    Matrix c(a*b);
    cout << c;
}

