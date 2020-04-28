#pragma once
//Simple Comparator classes that just use "size" for comparison

template <typename T>
class HighToLow
{
public:
    bool operator()(const T &a, const T &b) const
    {
        return a > b;
    }
};

template <typename T>
class LowToHigh
{
public:
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};

//Templated on an entry data type that supports the key() function
template <typename E>
class EntryCompare
{
public:
    bool operator()(const E &a, const E &b) const
    {
        return a.key() < b.key();
    }
};
