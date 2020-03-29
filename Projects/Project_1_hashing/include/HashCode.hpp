#pragma once
class HashCode
{
public:
    int operator()(int key)
    {
        return key;
    }
};