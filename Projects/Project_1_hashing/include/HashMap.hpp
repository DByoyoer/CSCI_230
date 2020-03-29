#pragma once
#include "Entry.hpp"
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

//Templated on key, value and hash function
template <typename K, typename V, typename H>
class ChainHashMap
{

public:
    class Iterator;

public:
    ChainHashMap(int capacity = 100)
        : n(0), table(capacity), probes(0) {}
    ChainHashMap(const std::vector<Entry<K, V>>& eList, float loadFactor);
    int size() const
    {
        return n;
    }
    bool empty() const
    {
        return n == 0;
    }
    Iterator find(const K& k, bool diagnostic = false);
    //diagnostic will print the probes want to turn off for loading file
    Iterator put(const K& k, const V& v, bool diagnostic = false);
    Iterator put(const Entry<K, V>& e, bool diagnostic = false);
    void erase(const K& k, bool diagnostic = false);
    void erase(const Iterator& p, bool diagnostic = false);
    void printAll();
    Iterator begin();
    Iterator end();

protected:
    typedef std::list<Entry<K, V>> Bucket;
    typedef std::vector<Bucket> BktArray;
    typedef typename BktArray::iterator BktIter;
    typedef typename Bucket::iterator ListIter;
    Iterator finder(const K& k);
    Iterator inserter(const Iterator& p, const Entry<K, V>& e);
    void eraser(const Iterator& p);
    static void nextEntry(Iterator& p)
    {
        ++p.ent;
    }
    static bool endOfBkt(Iterator& p)
    {
        return p.ent == p.bkt->end();
    }
    static bool isPrime(int n)
    {
        if (n < 2 || n % 2 == 0)
        {
            return false;
        }
        if (n == 2)
        {
            return true;
        }
        for (int div = 3; div <= sqrt(n); div += 2)
        {
            if (n % div == 0)
            {
                return false;
            }
        }
        return true;
    }

private:
    int n;
    H hash;
    BktArray table;
    int probes; //keeps track of probes during operations

public:
    class Iterator
    {
    private:
        BktIter bkt;
        ListIter ent;
        const BktArray* ba;

    public:
        Iterator(const BktArray& ba, const BktIter& bIt,
                 const ListIter& entIt = ListIter())
            : ba(&ba), bkt(bIt), ent(entIt) {}
        Entry<K, V>& operator*() const;
        bool operator==(const Iterator& p) const;
        Iterator& operator++();
        friend class ChainHashMap;
    };
};

//Iterator Class Definitions

template <typename K, typename V, typename H>
Entry<K, V>& ChainHashMap<K, V, H>::Iterator::operator*() const
{
    return *ent;
}

template <typename K, typename V, typename H>
bool ChainHashMap<K, V, H>::Iterator::operator==(const Iterator& p) const
{
    if (ba != p.ba || bkt != p.bkt)
    {
        return false;
    }
    else if (bkt == ba->end())
    {
        return true;
    }
    else
    {
        return (ent == p.ent);
    }
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator& ChainHashMap<K, V, H>::Iterator::operator++()
{
    ++ent;
    if (endOfBkt(*this))
    {
        ++bkt; //check next bucket
        while (bkt != ba->end() && bkt->empty())
        {
            ++bkt;
        }
        if (bkt == ba->end())
        {
            return *this;
        }
        ent = bkt->begin();
    }
    return *this;
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::end()
{
    return Iterator(table, table.end());
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::begin()
{
    if (empty())
    {
        return end();
    }
    BktIter bkt = table.begin();
    while (bkt->empty())
    {
        ++bkt;
    }
    return Iterator(table, bkt, bkt->begin());
}

template <typename K, typename V, typename H>
ChainHashMap<K, V, H>::ChainHashMap(const std::vector<Entry<K, V>>& eList, float loadFactor)
{

    int capacity = eList.size() / loadFactor;
    //finding size for table
    if (capacity % 2 == 0)
    {
        capacity++; //make it odd for easier prime checking
    }
    while (!isPrime(capacity))
    {
        capacity += 2;
    }
    table.resize(capacity);
    int probeSum = 0;
    int probeMax = 0;
    for (auto e : eList)
    {
        put(e);
        probeSum += probes;
        probeMax = std::max(probes, probeMax);
    }
    std::cout << "Table Size: " << table.size()
              << "\nAverage number of probes: " << (float)probeSum / eList.size()
              << "\nMax Probes: " << probeMax << std::endl;
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::finder(const K& k)
{
    probes = 1; //set to 1 because the initial index counts as a probe
    int i = hash(k) % table.size();
    BktIter bkt = table.begin() + i;
    Iterator p(table, bkt, bkt->begin());
    while (!endOfBkt(p) && (*p).key() != k)
    {
        probes++;
        nextEntry(p);
    }
    return p;
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::find(const K& k, bool diagnostic)
{
    Iterator p = finder(k);
    if (diagnostic)
    {
        std::cout << "Found/Not Found in " << probes << " probes.\n";
    }
    if (endOfBkt(p))
        return end();
    else
        return p;
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::inserter(const Iterator& p, const Entry<K, V>& e)
{
    ListIter ins = p.bkt->insert(p.ent, e);
    n++;
    return Iterator(table, p.bkt, ins);
}

template <typename K, typename V, typename H> // insert/replace (v,k)
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::put(const K& k, const V& v, bool diagnostic)
{
    Iterator p = finder(k);
    if (diagnostic)
    {
        std::cout << "Inserted in " << probes << " probes.\n";
    }
    if (endOfBkt(p))
    {
        return inserter(p, Entry<K, V>(k, v));
    }
    else
    {
        p.ent->setValue(v);
        return p;
    }
}

template <typename K, typename V, typename H>
typename ChainHashMap<K, V, H>::Iterator ChainHashMap<K, V, H>::put(const Entry<K, V>& e, bool diagnostic)
{

    return put(e.key(), e.value(), diagnostic);
}

template <typename K, typename V, typename H>
void ChainHashMap<K, V, H>::erase(const Iterator& p, bool diagnostic)
{
    eraser(p);
    if (diagnostic)
    {
        std::cout << "Removed in " << probes << " probes\n";
    }
}

template <typename K, typename V, typename H>
void ChainHashMap<K, V, H>::eraser(const Iterator& p)
{
    p.bkt->erase(p.ent);
    n--;
}

template <typename K, typename V, typename H>
void ChainHashMap<K, V, H>::erase(const K& k, bool diagnostic)
{
    Iterator p = finder(k);

    if (diagnostic)
    {
        std::cout << "Removed/searched in " << probes << " probes\n";
    }
    if (endOfBkt(p))
    {
        return;
    }
    eraser(p);
}

template <typename K, typename V, typename H>
void ChainHashMap<K, V, H>::printAll()
{
    Iterator p = begin();
    Iterator stop = end();
    while (!(p == stop))
    {
        std::cout << (*p).key() << ' ' << (*p).value() << '\n';
        ++p;
    }
}