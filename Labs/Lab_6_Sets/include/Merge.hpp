#pragma once
#include <list>

//Code provided by the book with slight format changes

template <typename E>
class Merge
{                                          // generic Merge
public:                                    // global types
    typedef std::list<E> List;             // list type
    void merge(List &A, List &B, List &C); // generic merge function
protected:                                 // local types
    typedef typename List::iterator Itor;  // iterator type
                                           // overridden functions
    virtual void fromA(const E &a, List &C) = 0;
    virtual void fromBoth(const E &a, const E &b, List &C) = 0;
    virtual void fromB(const E &b, List &C) = 0;
};

template <typename E> // generic merge
void Merge<E>::merge(List &A, List &B, List &C)
{
    Itor pa = A.begin(); // A's elements
    Itor pb = B.begin(); // B's elements
    while (pa != A.end() && pb != B.end())
    { // main merging loop
        if (*pa < *pb)
        {
            fromA(*pa++, C); // take from A
        }
        else if (*pa == *pb)
        {
            fromBoth(*pa++, *pb++, C); // take from both
        }
        else
        {
            fromB(*pb++, C); // take from B
        }
    }
    while (pa != A.end()) // take rest from A
    {
        fromA(*pa++, C);
    }
    while (pb != B.end()) // take rest from B
    {
        fromB(*pb++, C);
    }
}

template <typename E> // set intersection
class IntersectMerge : public Merge<E>
{
protected:
    typedef typename Merge<E>::List List;
    virtual void fromA(const E &a, List &C)
    {
    } // ignore
    virtual void fromBoth(const E &a, const E &b, List &C)
    {
        C.push_back(a);
    } // add a only
    virtual void fromB(const E &b, List &C)
    {
    } // ignore
};

template <typename E> // set union
class UnionMerge : public Merge<E>
{
protected:
    typedef typename Merge<E>::List List;
    virtual void fromA(const E &a, List &C)
    {
        C.push_back(a);
    } // add a
    virtual void fromBoth(const E &a, const E &b, List &C)
    {
        C.push_back(a);
    } // add a only
    virtual void fromB(const E &b, List &C)
    {
        C.push_back(b);
    } // add b
};

template <typename E> // set subtraction
class SubtractMerge : public Merge<E>
{
protected:
    typedef typename Merge<E>::List List;
    virtual void fromA(const E &a, List &C)
    {
        C.push_back(a);
    } // add a
    virtual void fromBoth(const E &a, const E &b, List &C)
    {
    } // ignore
    virtual void fromB(const E &b, List &C)
    {
    } // ignore
};