#include "Entry.hpp"
#include <vector>

template <typename K, typename V>
class VisitEntry : public Entry<K, V>
{
public:
    VisitEntry()
        : Entry<K, V>(), empty(true), available(true) {}

    VisitEntry(const K &k, const V &v)
        : Entry<K, V>(k, v), empty(false), available(false) {}

    bool available;
    bool empty;
};

template <typename K, typename V, typename H>
class OpenAddressMap
{
public:
    class Iterator;

    //data
protected:
    std::vector<VisitEntry<K, V>> table;
    int n;
    int probes;
    H hash;

    //helper functions
protected:
    //skips over erased entries
    virtual Iterator finder(const K &k);

    //different function used to find where to insert
    //will return first open spot
    virtual Iterator insertionFinder(const K &k);
    virtual void eraser(const Iterator &p);

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

public:
    OpenAddressMap(int size = 11) : n(0), probes(0), table(size){};

    //Can't be a constructor since it calls a virutal function
    //Also outputs average probes and max probes for insertion from list
    // to console for project
    virtual void createFromEntryList(const std::vector<Entry<K, V>> &eList,
                                     float loadFactor);
    Iterator find(const K &k);
    Iterator put(const Entry<K, V> &e);
    Iterator put(const K &k, const V &v);
    void erase(const Iterator &p);
    void erase(const K &k);
    Iterator end();
    Iterator begin();
    void printAll();

    int getLastProbe()
    {
        return probes;
    }
    bool empty() const
    {
        return n == 0;
    }
    int size()
    {
        return n;
    }

public:
    class Iterator
    {
    protected:
        typedef typename std::vector<VisitEntry<K, V>>::iterator vecItor;

    private:
        const std::vector<VisitEntry<K, V>> *tableRef;
        vecItor bktIt;

    public:
        Iterator(const std::vector<VisitEntry<K, V>> &table, const vecItor &it)
            : tableRef(&table), bktIt(it) {}
        Iterator &
        operator++();
        VisitEntry<K, V> &operator*() const;
        bool operator==(const Iterator &p) const;
        friend class OpenAddressMap;
    };
};

template <typename K, typename V, typename H>
VisitEntry<K, V> &OpenAddressMap<K, V, H>::
    Iterator::operator*() const
{
    return *bktIt;
}

template <typename K, typename V, typename H>
bool OpenAddressMap<K, V, H>::
    Iterator::operator==(const Iterator &p) const
{
    return (tableRef == p.tableRef && bktIt == p.bktIt);
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator &OpenAddressMap<K, V, H>::
    Iterator::operator++()
{
    ++bktIt;
    if (bktIt->available)
    {
        while (bktIt != tableRef->end() && bktIt->available)
        {
            ++bktIt;
        }
    }
    return *this;
}

template <typename K, typename V, typename H>
void OpenAddressMap<K, V, H>::
    createFromEntryList(const std::vector<Entry<K, V>> &eList, float loadFactor)
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
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    end()
{
    return Iterator(table, table.end());
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    begin()
{
    if (empty())
    {
        return end();
    }
    auto it = table.begin();
    while (it->empty)
    {
        ++it;
    }
    return Iterator(table, it);
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    finder(const K &k)
{
    probes = 1;
    int i = hash(k) % table.size();
    auto it = table.begin() + i;
    while (!it->empty && it->key() != k)
    {
        probes++;
        it++;
        if (it == table.end())
        {
            it = table.begin();
        }
    }
    return Iterator(table, it);
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    insertionFinder(const K &k)
{
    probes = 1;
    int i = hash(k) % table.size();
    auto it = table.begin() + i;
    while (!it->available && it->key() != k)
    {
        probes++;
        it++;
        if (it == table.end())
        {
            it = table.begin();
        }
    }
    return Iterator(table, it);
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    find(const K &k)
{
    Iterator p = finder(k);

    if ((*p).empty)
    {
        return end();
    }
    else
    {
        return p;
    }
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    put(const K &k, const V &v)
{
    n++;
    Iterator p = insertionFinder(k);
    (*p) = VisitEntry<K, V>(k, v);
    p.bktIt->empty = false;
    p.bktIt->available = false;
    return p;
}

template <typename K, typename V, typename H>
typename OpenAddressMap<K, V, H>::Iterator OpenAddressMap<K, V, H>::
    put(const Entry<K, V> &e)
{
    return put(e.key(), e.value());
}

template <typename K, typename V, typename H>
void OpenAddressMap<K, V, H>::eraser(const Iterator &p)
{
    //make it usable again
    (*p).available = true;

    n--;

    //reset entry to default
    (*p).setKey(K());
    (*p).setValue(V());
}

template <typename K, typename V, typename H>
void OpenAddressMap<K, V, H>::erase(const Iterator &p)
{
    eraser(p);
}

template <typename K, typename V, typename H>
void OpenAddressMap<K, V, H>::erase(const K &k)
{
    Iterator p = finder(k);
    eraser(p);
}

template <typename K, typename V, typename H>
void OpenAddressMap<K, V, H>::printAll()
{
    Iterator p = begin();
    Iterator stop = end();
    while (!(p == stop))
    {
        std::cout << (*p).key() << ' ' << (*p).value() << '\n';
        ++p;
    }
}

//Implements double hashing for resolving collisions
template <typename K, typename V, typename H>
class DoubleHashMap : public OpenAddressMap<K, V, H>
{
public:
    void createFromEntryList(const std::vector<Entry<K, V>> &eList,
                             float loadFactor) override
    {
        int capacity = eList.size() / loadFactor;
        //finding size for table
        if (capacity % 2 == 0)
        {
            capacity++; //make it odd for easier prime checking
        }
        while (!this->isPrime(capacity))
        {
            capacity += 2;
        }
        this->table.resize(capacity);
        int probeSum = 0;
        int probeMax = 0;

        collisionPrime = ((this->table.size()) - 1);
        if (collisionPrime % 2 == 0)
        {
            collisionPrime--;
        }
        while (!this->isPrime(collisionPrime))
        {
            collisionPrime -= 2;
        }
        std::cout << collisionPrime << "\n";
        for (auto e : eList)
        {
            this->put(e);
            probeSum += this->probes;
            probeMax = std::max(this->probes, probeMax);
        }
        std::cout << "Table Size: " << this->table.size()
                  << "\nAverage number of probes: " << (float)probeSum / eList.size()
                  << "\nMax Probes: " << probeMax << std::endl;
    }

protected:
    typedef typename OpenAddressMap<K, V, H>::Iterator Iterator;
    Iterator finder(const K &k) override
    {
        this->probes = 1;
        int counter = 1;
        int index = this->hash(k) % this->table.size();
        auto currentEntry = this->table[index];
        while (!currentEntry.empty && currentEntry.key() != k)
        {
            this->probes++;
            index = (this->hash(k) + counter * (collisionPrime - (k % collisionPrime))) % this->table.size();
            currentEntry = this->table[index];
            counter++;
        }
        return Iterator(this->table, this->table.begin() + index);
    }

    Iterator insertionFinder(const K &k) override
    {
        this->probes = 1;
        int counter = 1;
        int index = this->hash(k) % this->table.size();
        auto currentEntry = this->table[index];
        while (!currentEntry.available && currentEntry.key() != k)
        {
            this->probes++;
            index = (this->hash(k) + counter * (collisionPrime - (k % collisionPrime))) % this->table.size();
            currentEntry = this->table[index];
            counter++;
        }
        return Iterator(this->table, this->table.begin() + index);
    }

private:
    int collisionPrime;
};
