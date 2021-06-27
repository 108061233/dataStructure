#include<iostream>
#include <time.h>
#include <stdlib.h>
#include<string.h>

using namespace std;

template <class T>
void InsertionSort(T *a, const int n)
{ // sort a[1:n] into nondecreasing order
    int i;
    for (int j = 2; j <= n ; j++){
      a[0] = a[j];
      for (i = j - 1; a[i] > a[0]; i--)
      {
           a[i + 1] = a[i];
      }
      a[i + 1] = a[0];
    }
}

template <class T>
void QuickSort(T *a, const int left, const int right)
{ // sort a[left:right] into nondecreasing, a[left] as pivot
    if (left < right) {
        T & pivot = a[left];
        int i = left;
        int j = right + 1;
        do {
           do j--; while (a[j] > pivot);  //find a key ≤pivot
           do i++; while (a[i] <= pivot); //find a key >pivot

           if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(pivot, a[j]); //place the pivot between 2 lists
        QuickSort(a, left, j - 1);  // recursion
        QuickSort(a, j + 1, right); // recursion
    }
}

template <class T>
void Merge(T *a, T *b, const int k, const int m, const int n)
{ // a[k:m], a[m+1:n] are sorted, merged to b[k:n]
    int i1, i2, i3;
    for (i1 = k, i2 = m+1, i3 = k; i1 <= m && i2 <= n; i3++) {
         if (a[i1] <= a [i2]) {
             b[i3] = a[i1];
             i1++;
         } else {
             b[i3] = a[i2];
             i2++;
         }
  }
    // copy remaining records, if any, of 1st sublist
    if(i2>n) copy (a+i1, a+m+1, b+i3);

    // copy remaining records, if any, of 2nd sublist
    if(i1>m) copy (a+i2, a+n+1, b+i3);
}

template <class T>
void MergePass(T *a, T *b, const int n, const int s)
{//adjacent pairs of sublist of size s are merged from a to b. n = # records in a
    int i;
    for (i = 1; //i the first position in first of the sublists merged
            i <= n-(2*s)+1; //enough elements for 2 sublists of length s?
                i += 2*s) {
        Merge(a, b, i, i+s-1, i+(2*s)-1);
    }

    // merge remaining lists of size < 2*s
    if ((i + s-1) < n) //one full and one partial lists
        Merge(a, b, i, i+s-1, n);
    else               //only one partial lists remained
        copy(a+i, a+n+1, b+i);

}

template <class T>
void iMergeSort(T *a, const int n)
{ // sort a[1:n] into non-decreasing order
    T *tempList = new T[n+1];

    // s is the length of the currently merged sublist
    for (int s = 1; s < n; s *= 2)
    {
        MergePass(a, tempList, n, s);

        s *= 2;
        MergePass(tempList, a, n, s);
    }
    delete [] tempList;
}

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{
	int i1, i2, iResult = 0;
	for (i1 = start1, i2 =start2; i1 && i2; )
		if (a[i1] <= a[i2]) {
			link[iResult] = i1;
			iResult = i1; i1 = link[i1];}
		else {
			link[iResult] = i2;
			iResult = i2; i2 =link[i2];	}

	if (i1 == 0) link[iResult] = i2;
	else link[iResult] = i1;
	return link[0];
}

template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{

	if (left >= right) return left; //base case
	int mid = (left + right) /2;
	return ListMerge(a, link,
   		rMergeSort(a, link, left, mid),
  			rMergeSort(a, link, mid + 1, right));
}

template <class T>
void Adjust(T *a, const int root, const int n)
{
    // two subtrees are max heaps already
    // same procedure as the trickling-down procedure
    T e = a[root];
    //2*root is root's left child
    int j;
    for (j = 2*root; j <= n; j *=2) {
        if (j < n && a[j] < a[j+1]) // j and j+1 are siblings
            j++; // make j be the max child
        if (e >= a[j])
            break;
        a[j / 2] = a[j]; // move jth record up the path
    }
    a[j / 2] = e;
}

template <class T>
void HeapSort(T *a, const int n)
{// sort a[1..n] into non-decreasing order
 // a[n/2] is the parent of the last node, a[n]
    for (int i = n/2; i >= 1; i--) // buttom-up heapification
       Adjust(a, i, n);// make the tree rooted at i be a max heap

    for (int i = n-1; i >= 1; i--) {
       swap(a[1], a[i+1]); // move one record from heap to list
       Adjust(a, 1, i);    // heapify
    }
}

int main()
{
    int i, link[21] = {0}, m;

    /*************char***********/

    char c[21] = {0};
    int r;

    srand(time(NULL));    // initialize the random number generator
    for (i=1; i < 21; i++)
    {
        r = rand() % 26;   // generate a random number
        c[i] = 'a' + r;            // Convert to a character from a-z
    }

    cout << "Randomly generate a list of 20 characters: " << endl;
    for (i = 1; i <= 20; i++)
        cout << c[i] << ' ';
    cout << endl;

    cout << "Enter the method to sort(1 is insertion, 2 is quick, 3 is two merge, 4 is heap): ";
    cin >> m;

    if (m == 1) {
        InsertionSort<char>(c, 20);
        cout << "InsertionSort: ";
        for (i = 1; i <= 20; i++)
            cout << c[i] << ' ';
        cout << endl;
    } else if (m == 2) {
        QuickSort<char>(c, 1, 20);
        cout << "QuickSort: ";
        for (i = 1; i <= 20; i++)
            cout << c[i] << ' ';
        cout << endl;
    } else if (m == 3) {
        iMergeSort<char>(c, 20);
        cout << "iMergeSort: ";
        for (i = 1; i <= 20; i++)
            cout << c[i] << ' ';
        cout << endl;

        i = 0;
        rMergeSort<char>(c, link, 1, 20);
        cout << "rMergeSort: ";
        while(link[i] != 0) {
            cout << c[link[i]] << ' ';
            i = link[i];
        }
        cout << endl;
    } else if (m == 4) {
        HeapSort<char>(c, 20);
        cout << "HeapSort: ";
        for (i = 1; i <= 20; i++)
            cout << c[i] << ' ';
        cout << endl;
    }

    /***************int****************/

    int a[21] = {0};
    link[21] = {0};

    srand(time(NULL));    // initialize the random number generator
    for (i=1; i < 21; i++)
    {
        a[i] = rand() % 100;   // generate a random number
    }

    cout << "Randomly generate a list of 20 integers: " << endl;
    for (i = 1; i <= 20; i++)
        cout << a[i] << ' ';
    cout << endl;

    cout << "Enter the method to sort(1 is insertion, 2 is quick, 3 is two merge, 4 is heap): ";
    cin >> m;

    if (m == 1) {
        InsertionSort<int>(a, 20);
        cout << "InsertionSort: ";
        for (i = 1; i <= 20; i++)
            cout << a[i] << ' ';
        cout << endl;
    } else if (m == 2) {
        QuickSort<int>(a, 1, 20);
        cout << "QuickSort: ";
        for (i = 1; i <= 20; i++)
            cout << a[i] << ' ';
        cout << endl;
    } else if (m == 3) {
        iMergeSort<int>(a, 20);
        cout << "iMergeSort: ";
        for (i = 1; i <= 20; i++)
            cout << a[i] << ' ';
        cout << endl;

        i = 0;
        rMergeSort<int>(a, link, 1, 20);
        cout << "rMergeSort: ";
        while(link[i] != 0) {
            cout << a[link[i]] << ' ';
            i = link[i];
        }
        cout << endl;
    } else if (m == 4) {
        HeapSort<int>(a, 20);
        cout << "HeapSort: ";
        for (i = 1; i <= 20; i++)
            cout << a[i] << ' ';
        cout << endl;
    }

    /************float**************/

    float f[21] = {0};
    link[21] = {0};

    srand(time(NULL));    // initialize the random number generator
    for (i=1; i < 21; i++)
    {
        f[i] = (float)rand() / 500.0;   // generate a random number
    }

    cout << "Randomly generate a list of 20 floats: " << endl;
    for (i = 1; i <= 20; i++)
        cout << f[i] << ' ';
    cout << endl;

    cout << "Enter the method to sort(1 is insertion, 2 is quick, 3 is two merge, 4 is heap): ";
    cin >> m;

    if (m == 1) {
        InsertionSort<float>(f, 20);
        cout << "InsertionSort: ";
        for (i = 1; i <= 20; i++)
            cout << f[i] << ' ';
        cout << endl;
    } else if (m == 2) {
        QuickSort<float>(f, 1, 20);
        cout << "QuickSort: ";
        for (i = 1; i <= 20; i++)
            cout << f[i] << ' ';
        cout << endl;
    } else if (m == 3) {
        iMergeSort<float>(f, 20);
        cout << "iMergeSort: ";
        for (i = 1; i <= 20; i++)
            cout << f[i] << ' ';
        cout << endl;

        i = 0;
        rMergeSort<float>(f, link, 1, 20);
        cout << "rMergeSort: ";
        while(link[i] != 0) {
            cout << f[link[i]] << ' ';
            i = link[i];
        }
        cout << endl;
    } else if (m == 4) {
        HeapSort<float>(f, 20);
        cout << "HeapSort: ";
        for (i = 1; i <= 20; i++)
            cout << f[i] << ' ';
        cout << endl;
    }

    /***********string****************/

    char s[21];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srand(time(NULL));

    for (int i = 1; i <= 20; i++)
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

    cout << "Randomly generate a list of 20 string objects(string1): " << endl;
    for (i = 1; i <= 20; i++)
        cout << s[i];
    cout << endl;

    cout << "Enter the method to sort(1 is insertion, 2 is quick, 3 is two merge, 4 is heap): ";
    cin >> m;

    if (m == 1) {
        InsertionSort<char>(s, 20);
        cout << "InsertionSort: ";
        for (i = 1; i <= 20; i++)
            cout << s[i];
        cout << endl;
    } else if (m == 2) {
        QuickSort<char>(s, 1, 20);
        cout << "QuickSort: ";
        for (i = 1; i <= 20; i++)
            cout << s[i];
        cout << endl;
    } else if (m == 3) {
        iMergeSort<char>(s, 20);
        cout << "iMergeSort: ";
        for (i = 1; i <= 20; i++)
            cout << s[i];
        cout << endl;

        i = 0;
        rMergeSort<char>(s, link, 1, 20);
        cout << "rMergeSort: ";
        while(link[i] != 0) {
            cout << s[link[i]];
            i = link[i];
        }
        cout << endl;
    } else if (m == 4) {
        HeapSort<char>(s, 20);
        cout << "HeapSort: ";
        for (i = 1; i <= 20; i++)
            cout << s[i];
        cout << endl;
    }

}

