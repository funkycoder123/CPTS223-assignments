#ifndef QUEUE_H
#define QUEUE_H

class queue
{
private:
    static const int MAX = 100;
    int data[MAX];
    int front, rear;

public:
    queue() : front(0), rear(0) {}

    bool isEmpty() const
    {
        return front == rear;
    }

    bool isFull() const
    {
        return rear == MAX;
    }

    int size() const
    {
        return rear - front;
    }

    bool enqueue(int item)
    {
        if (isFull())
        {
            return false; // queue is full
        }
        data[rear++] = item;
        return true;
    }

    bool dequeue(int &item)
    {
        if (isEmpty())
        {
            return false; // queue is empty
        }
        item = data[front++];
        return true;
    }

    bool peek(int &item) const
    {
        if (isEmpty())
        {
            return false; // queue is empty
        }
        item = data[front];
        return true;
    }
};

#endif // QUEUE_H
