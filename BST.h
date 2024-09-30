#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

template <typename Comparable>
class BST
{
public:
    BST() : root(nullptr) {}
    ~BST() { makeEmpty(); }
    void makeEmpty();

    const Comparable &findMin() const;
    const Comparable &findMax() const;

    bool contains(const Comparable &x) const;
    void insert(const Comparable &x);
    void remove(const Comparable &x);
    int treeSize() const;
    int treeHeight() const;
    void printInOrder() const;
    void printLevels() const;
    void printMaxPath() const;

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element(theElement), left(lt), right(rt) {}
    };

    BinaryNode *root;

    void makeEmpty(BinaryNode *&t);
    bool contains(const Comparable &x, BinaryNode *t) const;
    void insert(const Comparable &x, BinaryNode *&t);
    void remove(const Comparable &x, BinaryNode *&t);
    int treeSize(BinaryNode *t) const;
    int treeHeight(BinaryNode *t) const;
    void printInOrder(BinaryNode *t) const;
    void printMaxPath(BinaryNode *t) const;
};

template <typename Comparable>
void BST<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
}

template <typename Comparable>
bool BST<Comparable>::contains(const Comparable &x) const
{
    return contains(x, root);
}

template <typename Comparable>
void BST<Comparable>::insert(const Comparable &x)
{
    insert(x, root);
}

template <typename Comparable>
void BST<Comparable>::remove(const Comparable &x)
{
    remove(x, root);
}

template <typename Comparable>
int BST<Comparable>::treeSize() const
{
    return treeSize(root);
}

template <typename Comparable>
int BST<Comparable>::treeHeight() const
{
    return treeHeight(root);
}

template <typename Comparable>
void BST<Comparable>::printInOrder() const
{
    printInOrder(root);
}

template <typename Comparable>
void BST<Comparable>::printLevels() const
{
    if (!root)
        return;
    queue<BinaryNode *> q;
    q.push(root);
    while (!q.empty())
    {
        BinaryNode *current = q.front();
        q.pop();
        cout << current->element << " "; // Add space between elements..
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
    cout << endl; // Add newline at the end
}

template <typename Comparable>
void BST<Comparable>::printMaxPath() const
{
    printMaxPath(root);
}

// Private Helper Functions....

template <typename Comparable>
bool BST<Comparable>::contains(const Comparable &x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true; // Match
}

template <typename Comparable>
void BST<Comparable>::insert(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr); // Insert at leaf
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // Ignore the duplicates..
}

template <typename Comparable>
void BST<Comparable>::remove(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        return; // Item not found, do nothing..
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr)
    { // Two children
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

template <typename Comparable>
int BST<Comparable>::treeSize(BinaryNode *t) const
{
    if (t == nullptr)
        return 0;
    else
        return 1 + treeSize(t->left) + treeSize(t->right);
}

template <typename Comparable>
int BST<Comparable>::treeHeight(BinaryNode *t) const
{
    if (t == nullptr)
        return -1; // Convention: height of empty tree is -1..
    else
        return 1 + max(treeHeight(t->left), treeHeight(t->right));
}

template <typename Comparable>
void BST<Comparable>::printInOrder(BinaryNode *t) const
{
    if (t != nullptr)
    {
        printInOrder(t->left);
        cout << t->element << " "; // space between elements..
        printInOrder(t->right);
    }
}

template <typename Comparable>
void BST<Comparable>::printMaxPath(BinaryNode *t) const
{
    if (t != nullptr)
    {
        cout << t->element << " "; // space between elements..
        if (treeHeight(t->left) > treeHeight(t->right))
            printMaxPath(t->left);
        else
            printMaxPath(t->right);
    }
    cout << endl; // newline at the end..
}
#endif
