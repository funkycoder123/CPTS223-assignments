#include "OpenMP.h"
#include "Heap.h"

void runOpenMP()
{
    hello_world();
    calSum();
    calMax();
}

void runHeap()
{
    int data_size = 10000;
    int *data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = rand() % data_size;
    }

    // Create a min-heap
    auto *hp = new Heap<int>();
    for (int i = 0; i < data_size; ++i)
    {
        hp->push(data[i]);
    }

    // Sort these values using STL for verification
    std::vector<int> vect(data, data + data_size);
    std::sort(vect.begin(), vect.end());

    // Test by comparing pop results with the sorted values
    for (int i = 0; i < data_size; ++i)
    {
        // If push and pop are correctly implemented, assertions should pass
        assert(vect[i] == hp->pop());
    }

    std::cout << "(3) Test runHeap() assert pass!" << std::endl;

    // Cleanup
    delete[] data;
    delete hp;
}

int main(int argc, char *argv[])
{
    runOpenMP();
    runHeap();
    return 0;
}
