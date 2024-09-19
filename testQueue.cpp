#include "queue.h"
#include <iostream>

void testQueueSize(void)
{
    queue q;
    if (q.size() == 0)
    {
        std::cout << "Test passed:) Queue size is 0 for an empty queue." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Queue size is not 0 for an empty queue." << std::endl;
    }
}

void testQueueIsEmpty(void)
{
    queue q;
    if (q.isEmpty())
    {
        std::cout << "Test passed:) Queue is empty." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Queue is not empty." << std::endl;
    }
}

void testQueueIsFull(void)
{
    queue q;
    for (int i = 0; i < 100; ++i)
    {
        q.enqueue(i);
    }
    if (q.isFull())
    {
        std::cout << "Test passed:) Queue is full after 100 enqueues." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Queue is not full after 100 enqueues." << std::endl;
    }
}

void testQueueEnqueue(void)
{
    queue q;
    if (q.enqueue(10))
    {
        std::cout << "Test passed:) Enqueue successful." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Enqueue failed." << std::endl;
    }
}

void testQueueDequeue(void)
{
    queue q;
    q.enqueue(10);
    int item;
    if (q.dequeue(item) && item == 10)
    {
        std::cout << "Test passed:) Dequeue successful and item is correct." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Dequeue unsuccessful or item is incorrect." << std::endl;
    }
}

void testQueuePeek(void)
{
    queue q;
    q.enqueue(20);
    int item;
    if (q.peek(item) && item == 20)
    {
        std::cout << "Test passed:) Peek successful and item is correct." << std::endl;
    }
    else
    {
        std::cout << "Test failed:( Peek unsuccessful or item is incorrect." << std::endl;
    }
}
