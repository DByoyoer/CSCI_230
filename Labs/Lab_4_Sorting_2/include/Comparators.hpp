#ifndef COMPARATORS_HPP
#define COMPARATORS_HPP

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

#endif
