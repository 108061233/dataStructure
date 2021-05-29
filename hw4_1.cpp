#include <iostream>
#include "Queue.cpp"
#include "Stack.cpp"

using namespace std;

template <class T> class BinaryTree; //forward declaration
template <class T> istream& operator>> (istream& is, BinaryTree<T>& a);

template <class T>
class TreeNode {
friend class BinaryTree <T>;
friend istream& operator>> <>(istream& is, BinaryTree<T>& a);
public:
    TreeNode() {leftChild = rightChild = 0;}
    TreeNode(T& d, TreeNode<T>* l, TreeNode<T>* r);
private:
    T data;
    TreeNode <T> *leftChild;
    TreeNode <T> *rightChild;
};

template <class T>
TreeNode<T>::TreeNode(T& d, TreeNode<T>* l, TreeNode<T>* r)
{
    data = d;
    leftChild = l;
    rightChild = r;
}

template<class T>
class BinaryTree
{ // objects: A finite set of nodes either empty or consisting
  // of a root node, left BinaryTree and right BinaryTree
friend istream& operator>> <>(istream& is, BinaryTree<T>& a);
public:
    BinaryTree() {root = 0;} // constructor for an empty binary tree
    BinaryTree(BinaryTree<T>& s) {root = Copy(s.root);}

    bool IsEmpty()
    {
        if (!root) return true;
        else return false;
    } // return true iff the binary tree is empty

	BinaryTree<T> LeftSubtree(); // return the left subtree
    BinaryTree<T> RightSubtree();// return the right subtree
    T RootData() { if(root) return root->data; }  // return the data in the root node of *this

    void Visit(TreeNode<T> * p);

    void Inorder() { Inorder(root); }
    void Inorder(TreeNode<T> * p);

    void Preorder() { Preorder(root); }
    void Preorder(TreeNode<T> * p);

    void Postorder() { Postorder(root); }
    void Postorder(TreeNode<T> * p);

    void LevelOrder();

    void NonrecInorder();
    void NoStackInorder();

    TreeNode<T> *Copy(TreeNode<T> * p);
    bool Equal(TreeNode<T>* a, TreeNode<T>* b);
    bool operator == (const BinaryTree& t)
    { return Equal(root, t.root); }

private:
    TreeNode <T> *root;
};

template<class T>
istream& operator>> (istream& is, BinaryTree<T>& a)
{
    int n;
    int p1, q1;
    int tr = 1;
    Queue<TreeNode <T>*> temp;
    cout << "The number of nodes of tree:";
    is >> n;

    TreeNode<T> *p = a.root;
    TreeNode<T> *q = a.root;
    TreeNode<T> *r = a.root;
    for(int i = 0; i < n;)
    {
        if (!a.root)
        {
            a.root = new TreeNode<T>();
            r = a.root;
            cout << "Enter root data:";
            is >> a.root->data;
            cout << "Does root have leftchild? (1 is yes, 0 is no): ";
            is >> p1;
            cout << "Does root have rightchild? (1 is yes, 0 is no): ";
            is >> q1;
            i++;
        } else {
            if (p1) {
                cout << "Enter the data:";
                is >> p->data;
                i++;
                p1 = 0;
            } else if (q1) {
                cout << "Enter the data:";
                is >> q->data;
                i++;
                q1 = 0;
            } else {
                cout << "Dose node " << tr << " have leftchild? (1 is yes, 0 is no): ";
                is >> p1;
                cout << "Dose node " << tr << " have rightchild? (1 is yes, 0 is no): ";
                is >> q1;
            }
        }

        if (i < n) {
            if (!r->leftChild && p1)
            {
                r->leftChild = new TreeNode<T>();
                p = r->leftChild;
                temp.Push(p);
            } else if (!r->rightChild && q1) {
                r->rightChild = new TreeNode<T>();
                q = r->rightChild;
                temp.Push(q);
            } else {
                r = temp.Front();
                temp.Pop();
                p1 = 0;
                q1 = 0;
                tr++;
            }
        }
    }
    return is;
}

template <class T>
void BinaryTree<T>::Visit(TreeNode<T> * p)
{
    cout << p->data << " ";
}

template <class T>
void BinaryTree<T>::Inorder(TreeNode<T> * p)
{
    if(p) {
        Inorder(p->leftChild);
        Visit(p);
        Inorder(p->rightChild);
    }
}

template <class T>
void BinaryTree<T>::Preorder(TreeNode<T> * p)
{
    if(p) {
        Visit(p);
        Preorder(p->leftChild);
        Preorder(p->rightChild);
    }
}

template <class T>
void BinaryTree<T>::Postorder(TreeNode<T> * p)
{
    if(p) {
        Postorder(p->leftChild);
        Postorder(p->rightChild);
        Visit(p);
    }
}

template <class T>
void BinaryTree <T>::LevelOrder()
{
  Queue<TreeNode <T>*> q;
  TreeNode<T> *currentNode = root;
  while (currentNode) {
    Visit(currentNode);
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

template <class T>
TreeNode<T> * BinaryTree<T>::Copy(TreeNode<T> * p) // Workhorse
{//Return a pointer to an exact copy of the tree rooted at p
    if (!p) // a null pointer empty BT
      return 0;
    return new TreeNode<T>(p->data, Copy(p->leftChild), Copy(p->rightChild));
}

template<class T>
BinaryTree<T> BinaryTree<T>::LeftSubtree()
{
    BinaryTree<T> c;
    c.root = Copy(root->leftChild);
    return c;
}

template<class T>
BinaryTree<T> BinaryTree<T>::RightSubtree()
{
    BinaryTree<T> c;
    c.root = Copy(root->rightChild);
    return c;
}

template<class T>
bool BinaryTree<T>::Equal(TreeNode<T>* a, TreeNode<T>* b)
{
    if (!a && !b) return true;
    else return (a && b && (a->data == b->data) && Equal(a->leftChild, b->leftChild) && Equal(a->rightChild, b->rightChild));
}

template <class T>
void BinaryTree <T>::NonrecInorder()
{//nonrecursive inorder traversal
  Stack <TreeNode<T>*> s;
  TreeNode <T> *currentNode = root;
  while(1) {
    while (currentNode) {
      s.Push(currentNode);
      currentNode = currentNode->leftChild;
    }
    if (s.IsEmpty())
      return;
    currentNode = s.Top();
    s.Pop();
    Visit(currentNode);
    currentNode = currentNode->rightChild;
  }
}

template <class T>
void BinaryTree<T>:: NoStackInorder()
{
	if (!root) return;
	TreeNode<T> *top = 0, *lastRight =0, *p, *q, *r, *r1;
	p = q = root;
	while(1) {
	  while(1) {
	    if ((!p->leftChild) && (!p->rightChild)) {
        Visit(p);break;
      }
      if (!p->leftChild) {
        Visit(p);
        r = p->rightChild; p->rightChild = q;
        q = p; p = r;
      }
      else {
        r = p->leftChild; p->leftChild = q;
        q = p; p = r;
      }
    }
    TreeNode<T> *av = p;
    while(1) {
      if (p == root) return;
      if (!q->leftChild) {
        r = q->rightChild; q->rightChild = p;
        p = q; q = r;
      }
      else if (!q->rightChild) {
        r = q->leftChild; q->leftChild = p;
        p = q; q = r; Visit(p);
      }
      else
      {
         if (q == lastRight) {
         r = top; lastRight = r->leftChild;
         top = r->rightChild;
          r->leftChild = r->rightChild = 0;
          r = q->rightChild; q->rightChild = p;
          p = q; q = r;
        }
        else {
          Visit(q);
          av->leftChild = lastRight; av->rightChild = top;
          top = av; lastRight = q;
          r = q->leftChild; q->leftChild = p;
          r1 = q->rightChild; q->rightChild = r;
          p = r1;
          break;
        }
      }
    }
  }
}
int main(void)
{
    BinaryTree<int> a;
    cin >> a;
    BinaryTree<int> b(a);
    b.Inorder();
    cout << endl;
    b.NonrecInorder();
    cout << endl;
    b.NoStackInorder();

}
