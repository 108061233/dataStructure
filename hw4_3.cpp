#include <iostream>
#include "Queue.cpp"
#include "Stack.cpp"

using namespace std;

template <class K, class E> class BST;

template <class K, class E>
struct Pair { K first; E second;};

template <class K, class E>
class TreeNode {
friend class BST<K, E>;
public:
    TreeNode() {
        leftChild = rightChild = 0;
        leftSize = 1;
    }
    TreeNode(Pair<K, E> d) {
        leftChild = rightChild = 0;
        leftSize = 1;
        data = d;
    }
private:
    Pair<K, E> data;
    TreeNode <K, E> *leftChild;
    TreeNode <K, E> *rightChild;
    int leftSize;
};

template <class K, class E>
class Dictionary {
public:
    virtual bool IsEmpty() const = 0;  // return true if dictionary is empty

    virtual Pair<K, E>* Get(const K&) = 0;
    // return pointer to the pair w. specified key
    virtual Pair<K, E>* RankGet(int) = 0;

    virtual void Insert(const Pair <K, E>&) = 0;
    // insert the given pair; if key ia a duplicate, update associate element
    virtual void Delete(const K&) = 0;  // delete pair w. specified key

    virtual void Levelorder() = 0;
    virtual void Inorder() = 0;

    virtual void Split(const K&, BST<K, E>&, Pair<K, E>*&, BST<K, E>&) = 0;
};

template <class K, class E>
class BST : public Dictionary<K, E>
{
public:
    BST() {root = 0;}  // constructor
    bool IsEmpty() const
    {
        if (root == 0) return true;
        else return false;
    }; //return true iff empty

    Pair<K, E>* Get(const K& k);
    Pair<K, E>* RankGet(int r);

    void Insert(const Pair<K, E >& thePair);
    void Delete(const K& k);  // delete pair w. specified key

    void Split(const K& k, BST<K, E>& small, Pair<K, E>*& mid, BST<K, E>& big);
    void Levelorder();
    void Inorder();
private:
    TreeNode <K, E> *root;
};

template <class K, class E>
void BST<K, E> :: Insert(const Pair<K, E >& thePair)
{   // insert thePair into the BST
    // search for thePair.first¡App parent of p
    TreeNode <K, E> *p = root, *pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first) {
            p = p->leftChild;
            pp->leftSize++;
        }
        else if(thePair.first > p->data.first)p = p->rightChild;
        else // duplicate, update associated element
            { p->data.second = thePair.second; return;}
    }
    // perform insertion
    p = new TreeNode<K, E> (thePair);
    if (root) // tree is nonempty
        if (thePair.first < pp->data.first) {
            pp->leftChild = p;
        }
        else pp->rightChild = p;
    else root = p;
}

template <class K, class E>
Pair<K, E>* BST<K, E>::Get(const K& k)
{
    TreeNode <K, E> * currentNode = root;

    while (currentNode) {
        if (k < currentNode->data.first)
            currentNode = currentNode->leftChild;
        else if (k > currentNode->data.first)
            currentNode = currentNode->rightChild;
        else
            return & currentNode->data;
    }
    // no matching pair
    return 0;
}

template <class K, class E>
Pair<K, E>* BST<K, E>::RankGet(int r) //search by rank
{ //search the BST for the rth smallest pair
   TreeNode <K, E> * currentNode = root;
   while (currentNode) {
       if (r < currentNode -> leftSize)
          currentNode = currentNode -> leftChild;
       else if (r > currentNode -> leftSize)
       {
          r -= currentNode -> leftSize;
          currentNode = currentNode -> rightChild;
       }
       else return & currentNode -> data;
   }
   return 0;
}

template <class K, class E>
void BST<K, E>::Levelorder()
{
    if (IsEmpty()) cout << "BST is empty";
    else {
        Queue<TreeNode <K, E>*> q;
        TreeNode<K, E> *currentNode = root;
        while (currentNode) {
            cout << "<" << currentNode->data.first << ", " << currentNode->data.second << "> ";
            if (currentNode->leftChild)
                q.Push(currentNode->leftChild);

            if (currentNode->rightChild)
                q.Push(currentNode->rightChild);

            if (q.IsEmpty())
                return;
            currentNode = q.Front();
            q.Pop();
        }
    }
}

template <class K, class E>
void BST<K, E>::Inorder()
{//nonrecursive inorder traversal
    if (IsEmpty()) cout << "BST is empty";
    else {
        Stack <TreeNode<K, E>*> s;
        TreeNode <K, E> *currentNode = root;
        while(1) {
            while (currentNode) {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return;
        currentNode = s.Top();
        s.Pop();
        cout << "<" << currentNode->data.first << ", " << currentNode->data.second << "> ";
        currentNode = currentNode->rightChild;
        }
    }
}

template <class K, class E>
void BST<K, E>::Delete(const K& k)
{
    if (IsEmpty()) cout << "BST is empty";
    else {
        TreeNode <K, E> * currentNode = root, *pp = 0;

        while (currentNode) {
            if (currentNode->data.first != k)
                pp = currentNode;

            if (k < currentNode->data.first) {
                currentNode = currentNode->leftChild;
                pp->leftSize--;
            }
            else if (k > currentNode->data.first)
                currentNode = currentNode->rightChild;
            else break;
        }

        if (!currentNode) {
            cout << "The key does not exist." << endl;
            return;
        }

        TreeNode<K, E> *subNode = currentNode->leftChild;
        TreeNode<K, E> *PNode = currentNode;

        if (!subNode) {
            if (pp->leftChild == currentNode) pp->leftChild = 0;
            else pp->rightChild = 0;
            delete currentNode;
        } else {
            while (subNode->rightChild) {
                if (!subNode->rightChild->rightChild) PNode = subNode;
                subNode = subNode->rightChild;
            }

            if (PNode == currentNode) {
                currentNode->leftChild = subNode->leftChild;
                currentNode->data = subNode->data;
                currentNode->leftSize--;
                delete subNode;
            } else {
                if (subNode->leftChild) {
                    PNode->rightChild = subNode->leftChild;
                    currentNode->data = subNode->data;
                    currentNode->leftSize--;
                    delete subNode;
                } else {
                    currentNode->data = subNode->data;
                    currentNode->leftSize--;
                    delete subNode;
                }
            }
        }
    }
}

template <class K, class E>
void BST<K, E>::Split(const K& k, BST<K, E>& small, Pair<K, E>*& mid, BST<K, E>& big)
{ // Split the BST with respect to key k
    if (!root) {small.root = big.root = 0; return;} // empty tree
    // create temporary header nodes for small and big
    TreeNode<K, E> *sHead = new TreeNode<K, E>,
                    *s = sHead,
                    *bHead = new TreeNode<K, E>,
                    *b = bHead,
                    *currentNode = root;

    while (currentNode)
        if (k < currentNode->data.first){ // case 1
            b->leftChild = currentNode;
            b = currentNode; currentNode = currentNode->leftChild;
        }
        else if (k > currentNode->data.first) { // case 2
            s->rightChild = currentNode;
            s = currentNode; currentNode = currentNode->rightChild;
        }
        else { // case 3
            s->rightChild = currentNode->leftChild;
            b->leftChild = currentNode->rightChild;
            small.root = sHead->rightChild; delete sHead;
            big.root = bHead->leftChild; delete bHead;
            mid = new Pair<K, E>();
            mid->first = currentNode->data.first;
            mid->second = currentNode->data.second;
            delete currentNode;
            return;
        }
    // no pair with key k
    s->rightChild = b->leftChild = 0;
    small.root = sHead->rightChild; delete sHead;
    big.root = bHead->leftChild; delete bHead;
    mid = 0;
    return;
}

int main(void)
{
    Dictionary<int, char>* a;
    a = new BST<int, char>();
    int n;
    Pair<int, char> p;

    cout << "Enter the number of nodes want to insert: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the key: ";
        cin >> p.first;
        cout << "Enter the data: ";
        cin >> p.second;
        a->Insert(p);
    }

    cout << "BST in levelorder:" << endl;
    a->Levelorder();
    cout << endl;
    cout << "BST in inorder:" << endl;
    a->Inorder();
    cout << endl;

    cout << "The key of node want to get: ";
    cin >> n;
    cout << a->Get(n)->second << endl;

    cout << "The rank of node want to get: ";
    cin >> n;
    cout << a->RankGet(n)->second << endl;

    cout << "Enter the key want to delete: ";
    cin >> n;
    a->Delete(n);

    cout << "BST in levelorder:" << endl;
    a->Levelorder();
    cout << endl;
    cout << "BST in inorder:" << endl;
    a->Inorder();
    cout << endl;

    cout << "The key of node want to get: ";
    cin >> n;
    cout << a->Get(n)->second << endl;

    cout << "The rank of node want to get: ";
    cin >> n;
    cout << a->RankGet(n)->second << endl;

    cout << "The key want to split: ";
    cin >> n;
    BST<int, char> small, big;
    Pair<int, char>* mid;
    a->Split(n, small, mid, big);
    cout << "Small BST levelorder: " << endl;
    small.Levelorder();
    cout << endl;
    cout << "Small BST inorder: " << endl;
    small.Inorder();
    cout << endl;

    cout << "Big BST levelorder: " << endl;
    big.Levelorder();
    cout << endl;
    cout << "Big BST inorder: " << endl;
    big.Inorder();
    cout << endl;

    cout << "Mid: <" << mid->first << ", " << mid->second << ">";
}
