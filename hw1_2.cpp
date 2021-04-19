// Homework Information
//
// (35%) Write a C++ program to implement the ADT2.4 SparseMatrix in textbook (pp.97) (with Transpose implemented by FastTranspose).
// You should build you program based on the example codes in the book and implement the Add function and functions to input, output a sparse matrix by overloading the >> and << operators.
// You should try out at least two runs of your program to demonstrate the Add, Mult and input, output functions.
// 1. Add
// 2. Mult
// 3. input
// 4. output
//

#include <iostream>

using namespace std;

class SparseMatrix;

class MatrixTerm
{
friend class SparseMatrix;
friend ostream& operator<<(ostream& os, const SparseMatrix& a);
friend istream& operator>> (istream& is, SparseMatrix& a);
private:
    int row, col, value;
};

class SparseMatrix
{
public:
    SparseMatrix ();
    SparseMatrix(int r, int c, int t);
    SparseMatrix FastTranspose();
    SparseMatrix Mult(SparseMatrix b);
    SparseMatrix Add(SparseMatrix b);
    void ChangeSize1D(const int newSize);
    void StoreSum(const int sum, const int r, const int c);
    friend ostream& operator<<(ostream& os, const SparseMatrix& a);
    friend istream& operator>> (istream& is, SparseMatrix& a);
private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix()
{
    rows = 0;
    cols = 0;
}

SparseMatrix::SparseMatrix(int r, int c, int t)
{
    rows = r;
    cols = c;
    terms = t;
    capacity = t;
    smArray = new MatrixTerm[capacity];
}

SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b (cols, rows, terms);
    if (terms > 0)
    {
        int i;
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        fill (rowSize, rowSize + cols, 0);
        for (i = 0; i < terms; i++) rowSize[smArray[i].col]++;

        rowStart[0] = 0;
        for (i = 1; i < cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

        for(i = 0; i < terms; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}

void SparseMatrix::ChangeSize1D(const int newSize)
{
    if (newSize < terms)
        throw "New size must be >= number of terms";
    MatrixTerm *temp = new MatrixTerm[newSize];
    copy(smArray, smArray + terms, temp);
    delete[] smArray;
    smArray = temp;
    capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if (sum != 0)
    {
        if (terms == capacity)
            ChangeSize1D(2 * capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

SparseMatrix SparseMatrix::Mult(SparseMatrix b)
{
    if (cols != b.rows)
        throw "Incompatible matrices";
    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);
    int currRowIndex = 0,
        currRowBegin = 0,
        currRowA = smArray[0].row;

    if (terms == capacity)
        ChangeSize1D(terms + 1);
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;
    int sum = 0;
    while (currRowIndex < terms)
    { // 產生d的第currRowA列
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        { //*this的第CurrRowA列乘上b的第currColB行
            if (smArray[currRowIndex].row != currRowA)
            { //currRowA的結尾
                d.StoreSum(sum, currRowA, currColB);
                sum = 0; //重設sum
                currRowIndex = currRowBegin;
                //前進至下一行
                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;
                currColB = bXpose.smArray[currColIndex].row;
            }
            else if (bXpose.smArray[currColIndex].row != currColB)
            { // b中第currColB行的結尾
                d.StoreSum(sum, currRowA, currColB);
                sum = 0; // 重設
                // 第currRowA列改成與下一行相乘
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            }
            else if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
                currRowIndex++;
            else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
            { // 加到sum裡
                sum += smArray[currRowIndex].value *
                       bXpose.smArray[currColIndex].value;
                currRowIndex++;
                currColIndex++;
            }
            else
                currColIndex++;                       // currColB的下一項
        }                                             // while (currColIndex<= b.terms)結束
        while (smArray[currRowIndex].row == currRowA) // 前進至下一列
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    } // while (currRowIndex<terms)結束
    return d;
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    if (rows != b.rows || cols != b.cols)
        throw "Incompatible matrices";
    else
    {
        int aPos = 0, bPos = 0, cPos = 0;
        int capa = terms + b.terms; // the max needed capacity
        SparseMatrix c(rows, cols, capa);
        while (aPos < terms && bPos < b.terms)
        {
            if (smArray[aPos].row == b.smArray[bPos].row)
            {
                if (smArray[aPos].col == b.smArray[bPos].col)
                {
                    // remove the sum of value is 0
                    if ((smArray[aPos].value + b.smArray[bPos].value) != 0)
                    {
                        c.smArray[cPos].row = smArray[aPos].row;
                        c.smArray[cPos].col = smArray[aPos].col;
                        c.smArray[cPos++].value = smArray[aPos++].value + b.smArray[bPos++].value;
                    }
                    else
                    {
                        aPos++; bPos++;
                    }
                }
                else if (smArray[aPos].col < b.smArray[bPos].col)
                {
                    c.smArray[cPos++] = smArray[aPos++];
                }
                else
                {
                    c.smArray[cPos++] = b.smArray[bPos++];
                }
            }
            else if (smArray[aPos].row < b.smArray[bPos].row)
            {
                c.smArray[cPos++] = smArray[aPos++];
            }
            else
            {
                c.smArray[cPos++] = b.smArray[bPos++];
            }
        }
        for (; aPos < terms; aPos++) // the least_a matrix
        {
            c.smArray[cPos++] = smArray[aPos++];
        }
        for (; bPos < b.terms; bPos++) // the least b_matrix
        {
            c.smArray[cPos++] = b.smArray[bPos++];
        }
        c.terms = cPos; // the correct number of terms
        return c;
    }
}

ostream& operator<<(ostream& os, const SparseMatrix& a)
{
    cout << "The matrix is:" << endl;
    for (int aPos = 0; aPos < a.terms; aPos++)
    {
        cout << "Row :" << a.smArray[aPos].row << " ";
        cout << "Col :" << a.smArray[aPos].col << " ";
        cout << "Value :" << a.smArray[aPos].value << endl;
    }
    return os;
}

istream& operator>> (istream& is, SparseMatrix& a)
{
    int aPos = 0;
    for (; aPos < a.terms; aPos++)
    {
        cout << "Enter row:";
        is >> a.smArray[aPos].row;
        cout << "Enter col:";
        is >> a.smArray[aPos].col;
        cout << "Enter value:";
        is >> a.smArray[aPos].value;
    }
    return is;
}

int main(void)
{
    int terms, cols, rows;
    cout << "Enter matrix A terms:";
    cin >> terms;
    cout << "Enter matrix A cols:";
    cin >> cols;
    cout << "Enter matrix A rows:";
    cin >> rows;
    SparseMatrix a(rows, cols, terms);
    cin >> a;
    cout << a << endl;

    cout << "Enter matrix B terms:";
    cin >> terms;
    cout << "Enter matrix B cols:";
    cin >> cols;
    cout << "Enter matrix B rows:";
    cin >> rows;
    SparseMatrix b(rows, cols, terms);
    cin >> b;
    cout << b << endl;


    SparseMatrix c;
    c = a.Add(b);
    cout << "A + B = " <<endl;
    cout << c << endl;

    SparseMatrix d;
    d = a.Mult(b);
    cout << "A * B =" << endl;
    cout << d << endl;
    return 0;
}

// Input 1:
// Enter matrix A terms:3
// Enter matrix A cols:2
// Enter matrix A rows:2
// Enter row:0
// Enter col:0
// Enter value:2
// Enter row:1
// Enter col:0
// Enter value:5
// Enter row:1
// Enter col:1
// Enter value:5
// The matrix is:
// Row :0 Col :0 Value :2
// Row :1 Col :0 Value :5
// Row :1 Col :1 Value :5
//
// Enter matrix B terms:4
// Enter matrix B cols:2
// Enter matrix B rows:2
// Enter row:0
// Enter col:0
// Enter value:1
// Enter row:0
// Enter col:1
// Enter value:-2
// Enter row:1
// Enter col:0
// Enter value:1
// Enter row:1
// Enter col:1
// Enter value:6
// The matrix is:
// Row :0 Col :0 Value :1
// Row :0 Col :1 Value :-2
// Row :1 Col :0 Value :1
// Row :1 Col :1 Value :6
//
// A + B =
// The matrix is:
// Row :0 Col :0 Value :3
// Row :0 Col :1 Value :-2
// Row :1 Col :0 Value :6
// Row :1 Col :1 Value :11
//
// A * B =
// The matrix is:
// Row :0 Col :0 Value :2
// Row :0 Col :1 Value :-4
// Row :1 Col :0 Value :10
// Row :1 Col :1 Value :20

// Input 2:
// Enter matrix A terms:4
// Enter matrix A cols:2
// Enter matrix A rows:2
// Enter row:0
// Enter col:0
// Enter value:1
// Enter row:0
// Enter col:1
// Enter value:-1
// Enter row:1
// Enter col:0
// Enter value:1
// Enter row:1
// Enter col:1
// Enter value:1
// The matrix is:
// Row :0 Col :0 Value :1
// Row :0 Col :1 Value :-1
// Row :1 Col :0 Value :1
// Row :1 Col :1 Value :1
//
// Enter matrix B terms:4
// Enter matrix B cols:2
// Enter matrix B rows:2
// Enter row:0
// Enter col:0
// Enter value:2
// Enter row:0
// Enter col:1
// Enter value:1
// Enter row:1
// Enter col:0
// Enter value:2
// Enter row:1
// Enter col:1
// Enter value:5
// The matrix is:
// Row :0 Col :0 Value :2
// Row :0 Col :1 Value :1
// Row :1 Col :0 Value :2
// Row :1 Col :1 Value :5
//
// A + B =
// The matrix is:
// Row :0 Col :0 Value :3
// Row :1 Col :0 Value :3
// Row :1 Col :1 Value :6
//
// A * B =
// The matrix is:
// Row :0 Col :1 Value :-4
// Row :1 Col :0 Value :4
// Row :1 Col :1 Value :6
