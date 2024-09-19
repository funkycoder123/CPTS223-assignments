#include "testQueue.h"
#include <iostream>

int main()
{
    std::cout << "Running queue tests:" << std::endl;

    testQueueSize();
    testQueueIsEmpty();
    testQueueIsFull();
    testQueueEnqueue();
    testQueueDequeue();
    testQueuePeek();

    return 0;
}
