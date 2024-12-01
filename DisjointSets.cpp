#include "DisjointSets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjointSets::DisjointSets(int numElements) : s(numElements, -1)
{
}

/**
 * Union two disjoint sets using union by rank.
 */
void DisjointSets::unionSets(int root1, int root2)
{
    root1 = find(root1);
    root2 = find(root2);

    if (root1 == root2)
        return; // Already in the same set

    // Union by rank: attach smaller tree under the larger tree
    if (s[root1] < s[root2]) // root1 has larger rank (more negative value)
    {
        s[root1] += s[root2]; // Update size
        s[root2] = root1;     // Make root1 the parent
    }
    else
    {
        s[root2] += s[root1]; // Update size
        s[root1] = root2;     // Make root2 the parent
    }
}

/**
 * Perform a find (does not change anything).
 * Return the set containing x.
 */
int DisjointSets::find(int x) const
{
    while (s[x] >= 0)
        x = s[x]; // Follow the parent chain
    return x;
}

/**
 * Perform a find with path compression (the mutator version).
 * Return the set containing x.
 */
int DisjointSets::find(int x)
{
    if (s[x] < 0)
        return x; // x is the root

    // Path compression: make the parent point to the root directly
    return s[x] = find(s[x]);
}
