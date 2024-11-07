// Heap.h

#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <string>
#include <limits>

template <typename T>
class Heap
{

private:
    std::vector<T> _items;

    void percolateDown(unsigned int hole)
    {
        unsigned int child;
        T temp = _items[hole];

        while (hole * 2 <= _items.size() - 1)
        {
            child = hole * 2;
            if (child != _items.size() - 1 && _items[child + 1] < _items[child])
                child++;
            if (_items[child] < temp)
                _items[hole] = _items[child];
            else
                break;
            hole = child;
        }
        _items[hole] = temp;
    }

    void percolateUp(T item)
    {
        _items.push_back(item);
        int hole = _items.size() - 1;

        while (hole > 1 && item < _items[hole / 2])
        {
            _items[hole] = _items[hole / 2];
            hole /= 2;
        }
        _items[hole] = item;
    }

public:
    Heap() { _items.push_back(std::numeric_limits<T>::min()); }

    void push(T item)
    {
        percolateUp(item);
    }

    T pop()
    {
        long unsigned int last_index = _items.size() - 1;
        int root_index = 1;

        if (size() == 0)
        {
            throw std::out_of_range("pop() - No elements in heap");
        }

        T minItem = _items[root_index];

        _items[root_index] = _items[last_index];
        _items.pop_back();

        if (size() > 0)
        {
            percolateDown(1);
        }
        return minItem;
    }

    bool empty() const
    {
        return _items.size() == 1;
    }

    long unsigned int size() const
    {
        return _items.size() - 1;
    }

    std::string to_string() const
    {
        std::string ret = "";
        for (unsigned int i = 1; i < _items.size(); i++)
        {
            ret += std::to_string(_items[i]) + " ";
        }
        return ret;
    }
};

#endif
