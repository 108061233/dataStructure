//1.(30%) Write a C++ program to implement the ADT2.3 Polynomial (pp.88) using Representation 3 (dynamic array of (coef, exp) tuples).
//        Implement the Mult(Polynomial p) and Eval(float x). Estimate the computing time for Mult and Eval function.
//        Add two more functions to input and output polynomials via overloading the >> and << operators.
//        You should try out at least two runs of your program (execution trace) to demonstrate the Add, Mult, Eval and input, output functions.

#include <iostream>
using namespace std;

int coun = 0;

class Polynomial;

class Term {
friend Polynomial;
friend ostream& operator<<(ostream& os, const Polynomial& a);
friend istream& operator>> (istream& is, Polynomial& a);
private:
    float coef;
    int exp;
};

class Polynomial {
public:
    Polynomial();
    Polynomial Add(Polynomial b);
    Polynomial Mult(Polynomial b);
    float Eval(float f);
    friend ostream& operator<<(ostream& os, const Polynomial& a);
    friend istream& operator>> (istream& is, Polynomial& a);
private:
    Term *termArray;
    int capacity;
    int terms;
    void NewTerm(const float theCoeff, const int theExp);
};

Polynomial::Polynomial()
{
    capacity = 1;
    termArray = new Term[capacity];
    terms = 0;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
    if (terms == capacity)
    {
        capacity *= 2;
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}


Polynomial Polynomial::Add(Polynomial b)
{
    Polynomial c; //c.terms = 0
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms))
        if (termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t)
                c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp)
        {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else
        {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    //add in remaining terms of *this
    for (; aPos < terms; aPos++) //output the remaining terms
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

    //add in remaining terms of b
    for (; bPos < b.terms; bPos++) //output remaining terms
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

Polynomial Polynomial::Mult(Polynomial b)
{
    Polynomial temp[terms];
    Polynomial c;
    c.termArray[0].coef = 0;
    c.termArray[0].exp = 0;
    c.terms = 1;
    int aPos = 0, bPos = 0, cPos = 0;

    for (aPos = 0; aPos < terms; aPos++)
    {
        for (bPos = 0; bPos < b.terms; bPos++)
        {
            float t = termArray[aPos].coef * b.termArray[bPos].coef;
            int e = termArray[aPos].exp + b.termArray[bPos].exp;
            temp[cPos].NewTerm(t, e);
        }
        c = c.Add(temp[cPos++]);
    }
    return c;
}

ostream& operator<<(ostream& os, const Polynomial& a)
{
    int aPos = 0;
    os << "Polynomial is:" << endl;
    for (; aPos < a.terms; aPos++)
    {
        if (aPos != a.terms - 1)
            os << a.termArray[aPos].coef << "x ^ " << a.termArray[aPos].exp << " + ";
        else
            os << a.termArray[aPos].coef << "x ^ " << a.termArray[aPos].exp << endl;
    }
    return os;
}

istream& operator>>(istream& is, Polynomial& a)
{
    cout << "Enter the terms:";
    is >> a.terms;
    cout << "Enter the capacity:";
    is >> a.capacity;
    cout << "Enter coef and exp from exp high to low" << endl;
    for (int aPos = 0; aPos < a.terms; aPos++)
    {
        cout << "Enter the coef:";
        is >> a.termArray[aPos].coef;
        cout << "Enter the exp:";
        is >> a.termArray[aPos].exp;
    }
    return is;
}

float Polynomial::Eval(float f)
{
    int Pos = 0;
    float stor;
    float sum = 0;

    for(; Pos < terms; Pos++)
    {
        stor = 1;
        stor *= termArray[Pos].coef;
        for(int ord = 0; ord < termArray[Pos].exp; ord++)
            stor *= f;
        sum += stor;
    }
    return sum;
}

int main(void)

{
    float f;
    Polynomial a;
    Polynomial b;
    Polynomial c;
    cout << "Enter A polynomial:" << endl;
    cin >> a;
    cout << a;
    cout << "Enter B polynomial:" << endl;
    cin >> b;
    cout << b;

    cout << "A + B =" << endl;
    c = a.Add(b);
    cout << c;
    cout << "A * B =" << endl;
    c = a.Mult(b);
    cout << c;

    cout << "Enter evaluate number:" << endl;
    cin >> f;
    cout << "A(" << f << ") =" << a.Eval(f) << endl;
    cout << "B(" << f << ") =" << b.Eval(f) << endl;

    return 0;
}

// Big O of Mult:
// Let terms in A be 'm' and in B be 'n'.
// Big O of Mult is O(m(m + n)).
// If m > n, then big O of Mult is O(m^2).
// If m < n, then big O is O(mn).

// Big O of Eval:
// Let terms in polynomial be 'm'.
// If the max power in polynomial is greater than the others very much,
// then Big O is O(max power).
// If the powers in polynomial are close with 'n' and is greater than the others very much,
// then Big O is O(max power * n).
// If all powers in polynomial are close,
// then Big O is O(max power * m).

// Input 1:
// Enter A polynomial:
// Enter the terms:3
// Enter the capacity:3
// Enter coef and exp from exp high to low
// Enter the coef:2
// Enter the exp:2
// Enter the coef:1
// Enter the exp:1
// Enter the coef:1
// Enter the exp:0
// Polynomial is:
// 2x ^ 2 + 1x ^ 1 + 1x ^ 0
// Enter B polynomial:
// Enter the terms:4
// Enter the capacity:4
// Enter coef and exp from exp high to low
// Enter the coef:3
// Enter the exp:3
// Enter the coef:2
// Enter the exp:2
// Enter the coef:1
// Enter the exp:1
// Enter the coef:5
// Enter the exp:0
// Polynomial is:
// 3x ^ 3 + 2x ^ 2 + 1x ^ 1 + 5x ^ 0
// A + B =
// Polynomial is:
// 3x ^ 3 + 4x ^ 2 + 2x ^ 1 + 6x ^ 0
// A * B =
// Polynomial is:
// 6x ^ 5 + 7x ^ 4 + 7x ^ 3 + 13x ^ 2 + 6x ^ 1 + 5x ^ 0
// Enter evaluate number:
// 2
// A(2) =11
// B(2) =39

//Input 2:
// Enter A polynomial:
// Enter the terms:2
// Enter the capacity:2
// Enter coef and exp from exp high to low
// Enter the coef:1
// Enter the exp:10
// Enter the coef:2
// Enter the exp:3
// Polynomial is:
// 1x ^ 10 + 2x ^ 3
// Enter B polynomial:
// Enter the terms:2
// Enter the capacity:2
// Enter coef and exp from exp high to low
// Enter the coef:-1
// Enter the exp:10
// Enter the coef:2
// Enter the exp:6
// Polynomial is:
// -1x ^ 10 + 2x ^ 6
// A + B =
// Polynomial is:
// 2x ^ 6 + 2x ^ 3
// A * B =
// Polynomial is:
// -1x ^ 20 + 2x ^ 16 + -2x ^ 13 + 4x ^ 9 + 0x ^ 0
// Enter evaluate number:
// 1.5
// A(1.5) =64.415
// B(1.5) =-34.8838
