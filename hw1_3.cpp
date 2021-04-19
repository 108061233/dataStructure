//3.(35%) Write a C++ program to implement the ADT2.5 String (pp.114) (with Find function implemented by FastFind).
//        In addition, write two more functions: String::Delete(int start, int length); //remove length characters beginning at start
//        String::CharDelete(char c); //returns the string with all occurrence of c removed.
//        You should try out at least two runs of your program to demonstrate all those functions.

#include <iostream>

using namespace std;

class String
{
public:
    String ();
    String(char *init, int m);
    bool operator==(String t);
    int Length();
    String Concat(String t);
    String Substr(int i, int j);
    String Delete(int start, int len);
    String CharDelete(char c);
    void printf();
    int FastFind(String pat);
private:
    char *str;
    int *f;
    int length;
    void FailureFunction();
};

String::String()
{
    length = 0;
}

String::String(char *init, int m)
:length(m)
{
    str = new char[length];
    f = new int[length];
    for(int i = 0; i < length; i++)
        str[i] = init[i];
}

int String::Length()
{
    return length - 1;  // the length does not include '\0'
}

void String::FailureFunction()
{
    int lengthP = Length();
    f[0] = -1;
    for (int j = 1; j < lengthP; j++)
    {
        int i = f[j - 1];
        while ((*(str + j) != *(str + i + 1)) && (i >= 0)) i = f[i];
        if (*(str + j) == *(str + i + 1))
            f[j] = i + 1;
        else
            f[j] = -1;
    }
}

void String::printf()
{
    cout << str << endl;
}

int String::FastFind(String pat)
{
    pat.FailureFunction();
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while ((posP < lengthP) && (posS < lengthS))
        if (pat.str[posP] == str[posS])
        {
            posP++;
            posS++;
        }
        else
            if (posP == 0)
                posS++;
            else
                posP = pat.f[posP - 1] + 1;
    if (posP < lengthP) return -1;
    else return posS - lengthP;
}

String String::Concat(String t)
{
    int i = Length();
    char *temp = new char[Length() + t.Length() + 1];
    copy (str, str + Length(), temp);
    for (int j = 0; j < t.Length(); j++)
        temp[i++] = t.str[j]; // concat the string
    temp[i] = '\0'; // add the string end
    String c(temp, Length() + t.Length() + 1);
    delete []temp;
    return c;
}

bool String::operator==(String t)
{
    int coun = 0;
    if (Length() == t.Length())
        for (int i = 0; i < Length(); i++)
            if (str[i] == t.str[i]) coun++;

    if (coun == Length()) return true; // all of chars are the same
    else return false;
}

String String::Substr(int i, int j)
{
    int End = i + j;
    int t;
    char *temp = new char[j + 1];
    for (t = 0; i < End; i++)
        temp[t++] = str[i];
    temp[t] = '\0'; // add string end
    String c(temp, j + 1);
    delete [] temp;
    return c;
}

String String::Delete(int start, int len)
{
    int i = 0;
    int End = start + len - 1;
    int t;
    int lengthP = Length() - len; // the length we dont want to delete
    char *temp = new char[lengthP];
    for (t = 0; t < lengthP; i++)
        if (i > End || i < start)
            temp[t++] = str[i]; // store the char we dont to delete
    temp[t] = '\0';
    String c(temp, lengthP + 1);
    delete [] temp;
    return c;
}

String String::CharDelete(char c)
{
    int i;
    int r = 0;
    char *temp = new char[Length() + 1];
    for (i = 0; i < Length(); i++)
        if (str[i] != c)
            temp[r++] = str[i]; // store the char != c
    temp[r] = '\0';
    String s(temp, r + 1);
    delete [] temp;
    return s;
}

int main(void)
{
    int n;
    int pos;
    int start;
    int length;
    char cha;
    char A[100];
    char pat[100];
    cout << "Enter the length of A string:";
    cin >> n;
    cout << "Enter A string:";
    cin >> A;
    String a(A, n + 1);
    a.printf();
    cout << "Enter the length of pat string:";
    cin >> n;
    cout << "Enter pat string:";
    cin >> pat;
    String Pat(pat, n + 1);
    Pat.printf();

    if (a == Pat)
        cout << "The two strings are the same" << endl;
    else
        cout << "The two strings are not the same" << endl;

    String c;
    cout << "A concat pat is:" << endl;
    c = a.Concat(Pat);
    c.printf();

    cout << "The pos of pat in A is:" << endl;
    pos = a.FastFind(Pat);
    cout << pos;

    cout << endl << "Input start and length to find substring of A:"<< endl;
    cin >> start >> length;
    c = a.Substr(start, length);
    c.printf();

    cout << "Input start and length to delete substring of A:" << endl;
    cin >> start >> length;
    c = a.Delete(start, length);
    c.printf();

    cout << "Input the char want to delete:" << endl;
    cin >> cha;
    c = a.CharDelete(cha);
    c.printf();

    return 0;
}

// Input 1:
// Enter the length of A string:3
// Enter A string:abc
// abc
// Enter the length of pat string:3
// Enter pat string:abc
// abc
// The two strings are the same
// A concat pat is:
// abcabc
// The pos of pat in A is:
// 0
// Input start and length to find substring of A:
// 0
// 2
// ab
// Input start and length to delete substring of A:
// 0
// 1
// bc
// Input the char want to delete:
// b
// ac

// Input 2:
// Enter the length of A string:5
// Enter A string:Hello
// Hello
// Enter the length of pat string:5
// Enter pat string:World
// World
// The two strings are not the same
// A concat pat is:
// HelloWorld
// The pos of pat in A is:
// -1
// Input start and length to find substring of A:
// 1
// 3
// ell
// Input start and length to delete substring of A:
// 0
// 4
// o
// Input the char want to delete:
// l
// Heo
