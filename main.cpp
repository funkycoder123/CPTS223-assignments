// main.cpp
/*
Inserting the randomly generated integers into a BST generally gives a height in the order of:

answer: Average-case height of a BST is O(log n)
*/

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <random>
#include "BST.h"

void insertRandomIntegers(BST<int> *root, int numIntegers)
{
    const int minValue = -1000;
    const int maxValue = 1000;
    int randomInteger;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);

    for (int i = 0; i < numIntegers; ++i)
    {
        randomInteger = dist(rng);
        while (root->contains(randomInteger))
        {
            randomInteger = dist(rng);
        }
        root->insert(randomInteger);
    }
}

int main()
{
    BST<int> bst;

    // Insert a limited number of random integers
    insertRandomIntegers(&bst, 20);

    // Required output
    std::cout << "In-order Traversal:" << std::endl;
    bst.printInOrder();

    std::cout << "\nLevel-wise Traversal:" << std::endl;
    bst.printLevels();

    std::cout << "\nMax Path:" << std::endl;
    bst.printMaxPath();

    std::cout << "Tree Size: " << bst.treeSize() << std::endl;
    std::cout << "Tree Height: " << bst.treeHeight() << std::endl;

    return 0;
}
