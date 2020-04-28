#pragma once
#include <iostream>
template <typename K, typename V>
class Entry
{
public:
    Entry(const K &k = K(), const V &v = V())
        : _key(k), _value(v) {}
    const K &key() const
    {
        return _key;
    }
    const V &value() const
    {
        return _value;
    }
    void setKey(const K &k)
    {
        _key = k;
    }
    void setValue(const V &v)
    {
        _value = v;
    }

    friend std::ostream &operator<<(std::ostream &output, const Entry E)
    {
        output << '(' << E._key << ',' << E._value << ')';
        return output;
    }

private:
    K _key;
    V _value;
};