#include "experimentFunctions.h"
#include "AVLTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void runExperiment1()
{
    AVLTree<int> treeAsc, treeDesc, treeRand;
    const int n = 100; // Example range for odd numbers

    // Ascending order insertion
    for (int i = 1; i <= n; i += 2)
    {
        treeAsc.insert(i);
    }

    // Descending order insertion
    for (int i = n; i >= 1; i -= 2)
    {
        treeDesc.insert(i);
    }

    // Random order insertion
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= n; i += 2)
    {
        treeRand.insert(rand() % n + 1);
    }

    std::cout << "Experiment 1 - Test AVL Conditions:\n";
    std::cout << "Ascending Order - Average Depth: " << treeAsc.averageDepth() << "\n";
    std::cout << "Descending Order - Average Depth: " << treeDesc.averageDepth() << "\n";
    std::cout << "Random Order - Average Depth: " << treeRand.averageDepth() << "\n";
}
void runExperiment2()
{
    AVLTree<int> tree;
    const int n = 500; // Initial number of nodes

    // Insert random integers to create an initial tree structure
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i)
    {
        tree.insert(rand() % 1000);
    }

    double initialAverageDepth = tree.averageDepth();
    int initialSize = tree.treeSize();

    // Perform 5002 random insert/remove operations, ensuring a larger tree size
    for (int i = 0; i < 5002; ++i)
    {
        int insertVal = rand() % 1000;
        int removeVal = rand() % 1000;

        // Always perform the insertion
        tree.insert(insertVal);

        // Only perform a removal if the tree size is above 95% of initial size
        if (tree.treeSize() > (initialSize * 0.95))
        {
            tree.remove(removeVal);
        }
    }

    double finalAverageDepth = tree.averageDepth();
    int finalSize = tree.treeSize();

    std::cout << "Experiment 2 - Average Depth of AVL Tree\n";
    std::cout << "Initial Average Depth: " << initialAverageDepth << "\n";
    std::cout << "Final Average Depth: " << finalAverageDepth << "\n";
    std::cout << "Initial Tree Size: " << initialSize << "\n";
    std::cout << "Final Tree Size: " << finalSize << "\n";
}
