#pragma once
#include "Entry.hpp"
#include <vector>

//Templated on key, value and hash function
template <typename K, typename V, typename H>
class HashMap
{
private:
    int elementsStored;

public:
    class Iterator;

public:
    HashMap(int capacity = 100);
    int size() const
    {
        return elementsStored;
    }
    bool empty() const
    {
        return elementsStored == 0;
    }
    Iterator find(const K &k);
    Iterator put(const K &k, const V &v);
    Iterator put(Entry<K, V> &e);
    void erase(const K &k);
    void erase(const Iterator &p);
    Iterator begin();
    Iterator end();

protected:
    virtual Iterator finder(const K &k) = 0;
    virtual Iterator inserter(const Iterator &p, const Entry<K, V> &e);
    virtual void eraser(const Iterator &p);

public:
    class Iterator
    {
    public:
        Iterator() { p = 0; }

    private:
        int p;
    };
};
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K &k)
{
    Iterator p = finder(k);
    if (endOfBkt(p))
        return end();
    else
        return p;
}

template <typename K, typename V, typename H> // insert/replace (v,k)
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::put(const K &k, const V &v)
{
    Iterator p = finder(k); 
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
void HashMap<K, V, H>::erase(const Iterator &p)
{
    eraser(p);
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const K &k)
{
    Iterator p = finder(k);

    eraser(p);
}

template <typename K, typename V, typename H>
class ChainHashMap : public HashMap<K, V, H>
{
public:
    ChainHashMap(std::vector<Entry<K, V>>, double loadfactor) {}

protected:
    typedef typename HashMap<K, V, H>::Iterator Iterator;
    virtual Iterator finder(const K &key) { return Iterator(); }
    virtual Iterator inserter(const Iterator &p, const Entry<K, V> &e) { return Iterator(); };
    void eraser(const Iterator &p)
    {
        std::cout << "Doing stuff";
    };
};