#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class AVLTree {
private:
    struct AVLNode {
        T element;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const T& ele, AVLNode* lt = nullptr, AVLNode* rt = nullptr, int h = 0)
            : element(ele), left(lt), right(rt), height(h) {}
    };

    AVLNode* root;

    // Utility functions
    int height(AVLNode* t) const {
        return t == nullptr ? -1 : t->height;
    }

    void insert(const T& x, AVLNode*& t) {
        if (t == nullptr) {
            t = new AVLNode(x);
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }

        balance(t);
    }

    void remove(const T& x, AVLNode*& t) {
        if (t == nullptr) return;

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            AVLNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    AVLNode* findMin(AVLNode* t) const {
        return t == nullptr ? nullptr : (t->left == nullptr ? t : findMin(t->left));
    }

    AVLNode* findMax(AVLNode* t) const {
        return t == nullptr ? nullptr : (t->right == nullptr ? t : findMax(t->right));
    }

    bool contains(const T& x, AVLNode* t) const {
        if (t == nullptr) return false;
        if (x < t->element) return contains(x, t->left);
        if (x > t->element) return contains(x, t->right);
        return true;
    }

    void balance(AVLNode*& t) {
        if (t == nullptr) return;

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(AVLNode*& k2) {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AVLNode*& k1) {
        AVLNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AVLNode*& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AVLNode*& k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    void makeEmpty(AVLNode*& t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    int computeHeight(AVLNode* t) const {
        return t == nullptr ? -1 : max(computeHeight(t->left), computeHeight(t->right)) + 1;
    }

    int treeSize(AVLNode* t) const {
        return t == nullptr ? 0 : treeSize(t->left) + treeSize(t->right) + 1;
    }

    double averageDepth(AVLNode* t, int depth = 0) const {
        if (t == nullptr) return 0;
        return depth + averageDepth(t->left, depth + 1) + averageDepth(t->right, depth + 1);
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { makeEmpty(root); }

    void insert(const T& x) {
        insert(x, root);
    }

    void remove(const T& x) {
        remove(x, root);
    }

    bool contains(const T& x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    int height() const {
        return height(root);
    }

    int computeHeight() const {
        return computeHeight(root);
    }

    int treeSize() const {
        return treeSize(root);
    }

    double averageDepth() const {
        int size = treeSize(root);
        return size == 0 ? 0 : averageDepth(root) / size;
    }
};

#endif
