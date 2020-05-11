#pragma once
#include <list>

template <typename T>
class LinkedBinaryTree
{
protected:
    struct Node
    {
        T data;
        Node *parent;
        Node *left;
        Node *right;
        Node() : data(), parent(NULL), left(NULL), right(NULL) {}
    };

public:
    class Position
    {
    private:
        Node *v;

    public:
        Position(Node *u = NULL) : v(u){};

        T &operator*()
        {
            return v->data;
        }

        Position left() const
        {
            return Position(v->left);
        }

        Position right() const
        {
            return Position(v->right);
        }

        Position parent() const
        {
            return Position(v->parent);
        }

        bool isRoot() const
        {
            return v->parent == NULL;
        }

        bool isExternal() const
        {
            return v->right == NULL && v->left == NULL;
        }

        friend class LinkedBinaryTree;
    };

public:
    LinkedBinaryTree();
    ~LinkedBinaryTree();
    int size() const;
    bool empty() const;
    std::list<Position> positions(int traversal = 0) const;
    Position getRoot() const;
    void addRoot();
    void expandExternal(const Position &p, const T &value);
    Position removeAoveExternal(const Position &p);
    void destroyTree(Node *v);

protected:
    void preorder(Node *v, std::list<Position> &pl) const;
    void inorder(Node *v, std::list<Position> &pl) const;
    void postorder(Node *v, std::list<Position> &pl) const;
    void levelorder(Node *v, std::list<Position> &pl) const;

private:
    Node *root;
    int n;
};

template <typename T>
LinkedBinaryTree<T>::LinkedBinaryTree() : root(NULL), n(0) {}

template <typename T>
int LinkedBinaryTree<T>::size() const
{
    return n;
}

template <typename T>
bool LinkedBinaryTree<T>::empty() const
{
    return n == 0;
}

template <typename T>
typename LinkedBinaryTree<T>::Position LinkedBinaryTree<T>::getRoot() const
{
    return Position(root);
}

template <typename T>
void LinkedBinaryTree<T>::addRoot()
{
    root = new Node;
    n = 1;
}

template <typename T>
void LinkedBinaryTree<T>::expandExternal(const Position &p, const T &value)
{
    Node *expandingNode = p.v;
    expandingNode->data = value;
    expandingNode->left = new Node;
    expandingNode->left->parent = expandingNode;
    expandingNode->right = new Node;
    expandingNode->right->parent = expandingNode;
    n += 2;
}

template <typename T>
typename LinkedBinaryTree<T>::Position LinkedBinaryTree<T>::removeAoveExternal(const Position &p)
{
    Node *removeStart = p.v;
    Node *parentToRemove = removeStart->parent;
    Node *sibling = removeStart == parentToRemove->left ? parentToRemove->right : parentToRemove->left;

    if (parentToRemove == root)
    {
        root = sibling;
    }
    else
    {
        Node *grandParent = parentToRemove->parent;
        if (grandParent->left == parentToRemove)
        {
            grandParent->left = sibling;
        }
        else
        {
            grandParent->right = sibling;
        }
    }
    delete removeStart;
    delete parentToRemove;
    n -= 2;
    return Position(sibling);
}

template <typename T>
void LinkedBinaryTree<T>::preorder(Node *v, std::list<Position> &pl) const
{
    if (!Position(v).isExternal())
    {
        pl.push_back(Position(v));
    }
    if (v->left != NULL)
    {
        preorder(v->left, pl);
    }
    if (v->right != NULL)
    {
        preorder(v->right, pl);
    }
}

template <typename T>
void LinkedBinaryTree<T>::inorder(Node *v, std::list<Position> &pl) const
{
    if (v == NULL)
    {
        return;
    }
    inorder(v->left, pl);
    if (!Position(v).isExternal())
    {
        pl.push_back(Position(v));
    }
    inorder(v->right, pl);
}

template <typename T>
void LinkedBinaryTree<T>::postorder(Node *v, std::list<Position> &pl) const
{
    if (v == NULL)
    {
        return;
    }
    postorder(v->left, pl);
    postorder(v->right, pl);
    if (!Position(v).isExternal())
    {
        pl.push_back(Position(v));
    }
}

template <typename T>
void LinkedBinaryTree<T>::levelorder(Node *v, std::list<Position> &pl) const
{
    std::list<Node *> myQueue;
    Node *curNode;

    myQueue.push_back(v);
    while (!myQueue.empty())
    {
        curNode = myQueue.front();
        myQueue.pop_front();
        if (!Position(curNode).isExternal())
        {
            pl.push_back(Position(curNode));
        }
        if (curNode->left != NULL)
        {
            myQueue.push_back(curNode->left);
        }
        if (curNode->right != NULL)
        {
            myQueue.push_back(curNode->right);
        }
    }
}

template <typename T>
std::list<typename LinkedBinaryTree<T>::Position> LinkedBinaryTree<T>::positions(int traversal) const
{
    std::list<Position> pl;

    switch (traversal)
    {
    case 0:
        inorder(root, pl);
        break;
    case 1:
        preorder(root, pl);
        break;
    case 2:
        postorder(root, pl);
        break;
    case 3:
        levelorder(root, pl);
        break;

    default:
        break;
    }

    return pl;
}

template <typename T>
void LinkedBinaryTree<T>::destroyTree(Node *v)
{
    if (v != NULL)
    {
        destroyTree(v->left);
        v->left = NULL;
        destroyTree(v->right);
        v->right = NULL;
        delete v;
    }
}

template <typename T>
LinkedBinaryTree<T>::~LinkedBinaryTree()
{
    destroyTree(root);
}
