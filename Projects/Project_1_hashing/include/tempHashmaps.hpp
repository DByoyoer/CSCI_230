#pragma once

#include <vector>
#include <list>
#include "Entry.hpp"

template <typename K, typename V, typename H>
class ChainHashTable
{
private:
    int numberOfElements;
    std::vector<std::list<Entry>> bucketArray;

public:
    typedef Entry<K, V> Entry;
};
