/*
Inserting the randomly generated integers into a BST generally gives a height in the order of:

Your answer: Average-case height of a BST is O(log n).......

*/

#include <cstdlib> // For rand() and srand()....
#include <ctime>   // For time()...
#include <chrono>
#include <cmath>
#include <random>
#include "BST.h"

double log2(double d)
{
    return log(d) / log(2); // log() use e as base..
}

void insertRandomIntegers(BST<int> *root, int numIntegers)
{
    // The range of random integers
    const int minValue = -1000000000;
    const int maxValue = 1000000000;
    int randomInteger;

    // Generate a uniform distribution to generate random integers
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);

    // Generate random integers (without duplicates) from the specified range..
    for (int i = 0; i < numIntegers; ++i)
    {
        randomInteger = dist(rng);
        while (root->contains(randomInteger) == true)
        {
            randomInteger = dist(rng);
        }
        root->insert(randomInteger);
    }
}

int main()
{
    BST<int> bst;

    // Insert 100 random integers
    insertRandomIntegers(&bst, 100);

    // Print BST contents
    cout << "In-order Traversal:" << endl;
    bst.printInOrder();

    cout << "Level-wise Traversal:" << endl;
    bst.printLevels();

    cout << "Max Path:" << endl;
    bst.printMaxPath();

    cout << "Tree Size: " << bst.treeSize() << endl;
    cout << "Tree Height: " << bst.treeHeight() << endl;

    return 0;
}
