
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

template <typename E>
class EntryLowToHigh
{
    bool operator()(const E &a, const E &b) const
    {
        return a.key() < b.key();
    }
};
