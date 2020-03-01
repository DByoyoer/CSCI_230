#include "Entry.hpp"
#include <list>
#include <vector>

template <typename K, typename V, typename H>
class HashMap
{
public:                                   // public types
    typedef Entry<const K, V> Entry;      // a (key,value) pair
    class Iterator;                       // a iterator/position
public:                                   // public functions
    HashMap(int capacity = 100);          // constructor
    int size() const;                     // number of entries
    bool empty() const;                   // is the map empty?
    Iterator find(const K& k);            // find entry with key k
    Iterator put(const K& k, const V& v); // insert/replace (k,v)
    void erase(const K& k);               // remove entry with key k
    void erase(const Iterator& p);        // erase entry at p
    Iterator begin();                     // iterator to first entry
    Iterator end();                       // iterator to end entry
protected:                                // protected types
    typedef std::list<Entry> Bucket;      // a bucket of entries
    typedef std::vector<Bucket> BktArray; // a bucket array
                                          // ...insert HashMap utilities here
private:
    int n;      // number of entries
    H hash;     // the hash comparator
    BktArray B; // bucket array
public:         // public types
                // ...insert Iterator class declaration here
};
