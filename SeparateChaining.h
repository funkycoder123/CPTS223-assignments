#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
public:
    explicit ChainingHash(int size = 101) : theLists(nextPrime(size)), currentSize{0} {}

    bool contains(const HashedObj &x) const
    {
        auto &whichList = theLists[myhash(x)];
        return std::find(begin(whichList), end(whichList), x) != end(whichList);
    }

    void makeEmpty()
    {
        for (auto &thisList : theLists)
        {
            thisList.clear();
        }
        currentSize = 0;
    }

    bool insert(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        if (std::find(begin(whichList), end(whichList), x) != end(whichList))
        {
            return false;
        }

        whichList.push_back(x);
        if (++currentSize > theLists.size())
        {
            rehash();
        }
        return true;
    }

    bool insert(HashedObj &&x)
    {
        auto &whichList = theLists[myhash(x)];
        if (std::find(begin(whichList), end(whichList), x) != end(whichList))
        {
            return false;
        }

        whichList.push_back(std::move(x));
        if (++currentSize > theLists.size())
        {
            rehash();
        }
        return true;
    }

    bool remove(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        auto itr = std::find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
        {
            return false;
        }

        whichList.erase(itr);
        --currentSize;
        return true;
    }

    double readLoadFactor()
    {
        return loadFactor();
    }

    double readCurrentSize()
    {
        return currentSize;
    }

    double readArraySize()
    {
        return theLists.size();
    }

private:
    vector<list<HashedObj>> theLists;
    std::size_t currentSize;

    void rehash()
    {
        vector<list<HashedObj>> oldLists = theLists;
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto &thisList : theLists)
        {
            thisList.clear();
        }

        currentSize = 0;
        for (auto &thisList : oldLists)
        {
            for (auto &x : thisList)
            {
                insert(std::move(x));
            }
        }
    }

    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

    double loadFactor()
    {
        return static_cast<double>(currentSize) / theLists.size();
    }
};

#endif