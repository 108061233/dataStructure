#include<iostream>
#include<string.h>

using namespace std;

class SymbolTable2;

template <class T>
class Node{
friend class SymbolTable2;
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

class SymbolTable1 {
public:
    SymbolTable1(){};
    void Insert(string key);
    pair<char, string>* Search(string key);
    void Print();
private:
    pair<char, string>* ht[26] = {0};
};

void SymbolTable1::Insert(string key)
{

    int i, n;
    char c;
    for (n = 0, c = 'a'; c < 'a' + 26; c++, n++) {
        if (c == key[0]) {
            i = n;
            break;
        }
    }

    if (!ht[i]) {
        ht[i] = new pair<char, string> (key[0], key);
    } else {
        int j;
        for (j = i; ht[j] != 0;)
            j = (j + 1) % 26;

        ht[j] = new pair<char, string> (key[0], key);
    }
}

pair<char, string>* SymbolTable1::Search(string key)
{ // search the linear probing hash table ht¡]each bucket has exactly one
     // slot¡^for k.  If a pair with this key is found, return a pointer to this pair;
     // otherwise, return 0
    int i, n;
    char c;
    for (n = 0, c = 'a'; c < 'a' + 26; c++, n++)
        if (c == key[0]) i = n;
	int j;
	for (j = i ;ht[j] && ht[j]->second != key;) {
		j = (j + 1 ) % 26;   // treat the table as circular
		if ( j == i ) return 0;// back to the start point
	}
	if(ht[j] && ht[j]->second == key) return ht[j];
	return 0;
}

void SymbolTable1::Print()
{
    char c;
    for (int i = 0; i < 26; i++) {
        c = 'a' + i;
        if (ht[i])
            cout << "HashTable[" << c << "]: " << ht[i]->second << endl;
        else
            cout << "HashTable[" << c << "]: " << 0 << endl;
    }
}

class SymbolTable2 {
public:
    SymbolTable2(){};
    void Insert(string key);
    pair<char, string>* Search(string key);
    void Print();
private:
    Node<pair<char, string>>* ht[26] = {0};
};

void SymbolTable2::Insert(string key)
{

    int i, n;
    char c;
    for (n = 0, c = 'a'; c < 'a' + 26; c++, n++) {
        if (c == key[0]) {
            i = n;
            break;
        }
    }

    if (!ht[i]) {
        pair<char, string> p(key[0], key);
        ht[i] = new Node<pair<char, string>> (p, 0);
    } else {
        Node<pair<char, string>> *curNode = ht[i];

        while (curNode->link != 0) curNode = curNode->link;
        pair<char, string> p(key[0], key);
        curNode->link = new Node<pair<char, string>> (p, 0);
    }
}

pair<char, string>* SymbolTable2::Search(string key)
{ // search the linear probing hash table ht¡]each bucket has exactly one
     // slot¡^for k.  If a pair with this key is found, return a pointer to this pair;
     // otherwise, return 0
    int i, n;
    char c;
    for (n = 0, c = 'a'; c < 'a' + 26; c++, n++)
        if (c == key[0]) i = n;

	Node<pair<char, string>> *curNode = ht[i];

	while (curNode != 0) {
        if (curNode->data.second == key) return &curNode->data;
        curNode = curNode->link;
	}
	return 0;
}

void SymbolTable2::Print()
{
    char c;
    for (int i = 0; i < 26; i++) {
        c = 'a' + i;
        if (ht[i]) {
            Node<pair<char, string>> *curNode = ht[i];
            cout << "HashTable[" << c << "]: ";
            while (curNode != 0) {
                cout << curNode->data.second << " ";
                curNode = curNode->link;
            }
            cout << endl;
        } else cout << "HashTable[" << c << "]: " << 0 << endl;
    }
}

int main()
{
    SymbolTable1 d1;
    string k[10];
    string s;

    /**********SymbolTable1************/
    cout << "SymbolTable1" << endl;
    cout << "Enter 10 keys to insert: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Enter the string key: ";
        cin >> k[i];
    }

    for (int i = 0; i < 10; i++)
        d1.Insert(k[i]);

    cout << "Hash Table is : " << endl;
    d1.Print();

    cout << "Enter 5 keys to search: " << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Enter the key want to search: ";
        cin >> s;

        if (d1.Search(s))
            cout << "Searched key is found, key is: " << d1.Search(s)->second;
        else cout << "Key is not found.";
        cout << endl;
    }

    /**********SymbolTable2************/
    SymbolTable2 d2;

    cout << "SymbolTable2" << endl;
    cout << "Enter 10 keys to insert: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Enter the string key: ";
        cin >> k[i];
    }

    for (int i = 0; i < 10; i++)
        d2.Insert(k[i]);

    cout << "Hash Table is : " << endl;
    d2.Print();

    cout << "Enter 5 keys to search: " << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Enter the key want to search: ";
        cin >> s;

        if (d2.Search(s))
            cout << "Searched key is found, key is: " << d2.Search(s)->second;
        else cout << "Key is not found.";
        cout << endl;
    }


}
