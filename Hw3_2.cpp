#include<iostream>

using namespace std;

class Polynomial;

struct Term {
   double coef;
   int exp;
   Term Set(double c, int e) { coef=c; exp=e; return *this; }
};

template <class T>
class Node{
friend class Polynomial;
friend ostream& operator<< (ostream& os, Polynomial& a);
friend istream& operator>> (istream& is, Polynomial& a);
public:
    Node(Node<T> *b) {link = b;}
    Node(T& a, Node<T> *b) {
        data = a;
        link = b;
    }
private:
    T data;
    Node<T> *link;
};

static Node<Term> *av = new Node<Term>(0);

class Polynomial{
public:
    Polynomial() {
        head = GetNode();
        head->link = head;
    }
    Polynomial(const Polynomial& b);
    ~Polynomial();
    Polynomial operator= (const Polynomial& b);
    Polynomial operator+ (const Polynomial& b) const;
    Polynomial operator- (const Polynomial& b) const;
    Polynomial operator* (const Polynomial& b) const;
    double Evaluate(double x) const;
    Node<Term>* GetNode() const;
    void RetNode(Node<Term> *&x) const;
    friend ostream& operator<< (ostream& os, Polynomial& a);
    friend istream& operator>> (istream& is, Polynomial& a);
private:
    Node<Term> *head;
};

Node<Term>* Polynomial::GetNode() const
{
    // Provide a node for use
    Node<Term>* x;
    if (av){
        x = av;
        av = av->link;
    }else{ // out of available nodes
        x = new Node<Term>(head);
    }
    return x;
}

void Polynomial::RetNode(Node<Term> *&x) const
{// Free the node pointed to by x
    x->link = av;
    av = x;
    x = 0; // not delete x
}

Polynomial::Polynomial(const Polynomial& b)
{
    head = GetNode();
    head->link = head;
    Node<Term> *BNode = b.head->link;
    Node<Term> *temp;
    Node<Term> *curNode = head;

    while (BNode != b.head) {
        temp = GetNode();
        temp->data.coef = BNode->data.coef;
        temp->data.exp = BNode->data.exp;
        temp->link = head;
        curNode->link = temp;
        curNode = temp;
        BNode = BNode->link;
    }
}

Polynomial::~Polynomial()
{
    Node<Term> *delNode;
    Node<Term> *curNode = head->link;
    while (curNode != head) {
        delNode = curNode;
        curNode = curNode->link;
        RetNode(delNode);
    }
    head->link = head;
}

istream& operator>> (istream& is, Polynomial& a)
{
    int n;
    double c;
    double e;
    cout << "Enter the number of terms: ";
    is >> n;
    a.head->data.coef = n;

    Node<Term> *cur = a.head;
    Node<Term> *temp;
    for (int i = 0; i < n; i++) {
        cout << "Enter the coef: ";
        is >> c;
        cout << "Enter the exp: ";
        is >> e;
        temp = a.GetNode();
        temp->data.coef = c;
        temp->data.exp = e;
        temp->link = a.head;
        cur->link = temp;
        cur = temp;
    }
    return is;
}

ostream& operator<< (ostream& os, Polynomial& a)
{
    if (a.head->link == a.head) os << "Polynomial is empty." << endl;
    else {
        os << "Polynomial is:" << endl;
        Node<Term> *cur = a.head->link;
        while (cur != a.head) {
            if (cur->link != a.head) {
                os << cur->data.coef << " x ^ ";
                os << cur->data.exp << " + ";
                cur = cur->link;
            } else {
                os << cur->data.coef << " x ^ ";
                os << cur->data.exp << endl;
                cur = cur->link;
            }
        }
    }
    return os;
}

Polynomial Polynomial::operator+(const Polynomial& b) const
{
    Polynomial c;
    Node<Term> *ANode = head->link;
    Node<Term> *BNode = b.head->link;
    Node<Term> *temp;
    Node<Term> *curNode = c.head;

    while (ANode != head && BNode != b.head) {
        if (ANode->data.exp == BNode->data.exp) {
            double sum = ANode->data.coef + BNode->data.coef;
            if (sum) {
                temp = c.GetNode();
                temp->data.coef = sum;
                temp->data.exp = ANode->data.exp;
                temp->link = c.head;
                curNode->link = temp;
                curNode = temp;
            }
            ANode = ANode->link;
            BNode = BNode->link;
        } else if (ANode->data.exp < BNode->data.exp) {
            temp = c.GetNode();
            temp->data.coef = BNode->data.coef;
            temp->data.exp = BNode->data.exp;
            temp->link = c.head;
            curNode->link = temp;
            curNode = temp;
            BNode = BNode->link;
        } else {
            temp = c.GetNode();
            temp->data.coef = ANode->data.coef;
            temp->data.exp = ANode->data.exp;
            temp->link = c.head;
            curNode->link = temp;
            curNode = temp;
            ANode = ANode->link;
        }
    }

    while (ANode != head) {
        temp = c.GetNode();
        temp->data.coef = ANode->data.coef;
        temp->data.exp = ANode->data.exp;
        temp->link = c.head;
        curNode->link = temp;
        curNode = temp;
        ANode = ANode->link;
    }

    while (BNode != b.head) {
        temp = c.GetNode();
        temp->data.coef = BNode->data.coef;
        temp->data.exp = BNode->data.exp;
        temp->link = c.head;
        curNode->link = temp;
        curNode = temp;
        BNode = BNode->link;
    }

    return c;
}

Polynomial Polynomial::operator-(const Polynomial& b) const
{
    Polynomial c;
    Node<Term> *ANode = head->link;
    Node<Term> *BNode = b.head->link;
    Node<Term> *temp;
    Node<Term> *curNode = c.head;

    while (ANode != head && BNode != b.head) {
        if (ANode->data.exp == BNode->data.exp) {
            double sum = ANode->data.coef - BNode->data.coef;
            if (sum) {
                temp = c.GetNode();
                temp->data.coef = sum;
                temp->data.exp = ANode->data.exp;
                temp->link = c.head;
                curNode->link = temp;
                curNode = temp;
            }
            ANode = ANode->link;
            BNode = BNode->link;
        } else if (ANode->data.exp < BNode->data.exp) {
            temp = c.GetNode();
            temp->data.coef = -(BNode->data.coef);
            temp->data.exp = BNode->data.exp;
            temp->link = c.head;
            curNode->link = temp;
            curNode = temp;
            BNode = BNode->link;
        } else {
            temp = c.GetNode();
            temp->data.coef = ANode->data.coef;
            temp->data.exp = ANode->data.exp;
            temp->link = c.head;
            curNode->link = temp;
            curNode = temp;
            ANode = ANode->link;
        }
    }

    while (ANode != head) {
        temp = c.GetNode();
        temp->data.coef = ANode->data.coef;
        temp->data.exp = ANode->data.exp;
        temp->link = c.head;
        curNode->link = temp;
        curNode = temp;
        ANode = ANode->link;
    }

    while (BNode != b.head) {
        temp = c.GetNode();
        temp->data.coef = -(BNode->data.coef);
        temp->data.exp = BNode->data.exp;
        temp->link = c.head;
        curNode->link = temp;
        curNode = temp;
        BNode = BNode->link;
    }

    return c;
}

Polynomial Polynomial::operator= (const Polynomial& b)
{
    Node<Term> *BNode = b.head->link;
    Node<Term> *temp;
    Node<Term> *curNode = head;

    while (BNode != b.head) {
        temp = GetNode();
        temp->data.coef = BNode->data.coef;
        temp->data.exp = BNode->data.exp;
        temp->link = head;
        curNode->link = temp;
        curNode = temp;
        BNode = BNode->link;
    }
    return *this;
}

Polynomial Polynomial::operator* (const Polynomial& b) const
{
    Polynomial stor[(int)head->data.coef];
    Polynomial c;
    Node<Term> *ANode = head->link;
    Node<Term> *temp;
    Node<Term> *curNode;
    int i = 0;

    while (ANode != head) {
        curNode = stor[i].head;
        Node<Term> *BNode = b.head->link;
        while (BNode != b.head) {
            temp = GetNode();
            temp->data.coef = ANode->data.coef * BNode->data.coef;
            temp->data.exp = ANode->data.exp + BNode->data.exp;
            temp->link = stor[i].head;
            curNode->link = temp;
            curNode = temp;
            BNode = BNode->link;
        }
        ANode = ANode->link;
        i++;
    }

    for (int n = 0; n < i; n++) {
        if (!n) c = stor[n];
        else c = c + stor[n];
    }

    for (int n = 0; n < i; n++) stor[n].~Polynomial();

    return c;
}

double Polynomial::Evaluate(double x) const
{
    double sum = 0;
    double temp = 0;
    Node<Term> *curNode = head->link;
    while (curNode != head) {
        temp = curNode->data.coef;
        for (int i = 0; i < curNode->data.exp; i++) temp = temp * x;
        sum += temp;
        curNode = curNode->link;
    }
    return sum;
}

int main(void)
{
    Node<Term> *temp;
    for (int i = 0; i < 30; i++) {
        temp = new Node<Term>(av);
        av = temp;
    }

    Polynomial a;
    cin >> a;
    cout << a;
    Polynomial b;
    cin >> b;
    Polynomial c(a * b);
    cout << c;
}
