#pragma once

class HuffmanNode
{
public:
    HuffmanNode(char c, int f, HuffmanNode *l, HuffmanNode *r)
    {
        data.first = c;
        data.second = f;
        left = l;
        right = r;
    }
    HuffmanNode(std::pair<char, int> d, HuffmanNode *l, HuffmanNode *r)
    {
        left = l;
        right = r;
        data = d;
    }
    int frequency()
    {
        return data.second;
    }
    char getChar()
    {
        return data.first;
    }
    bool isExternal()
    {
        return left == NULL && right == NULL;
    }
    HuffmanNode *getLeft()
    {
        return left;
    }
    HuffmanNode *getRight()
    {
        return right;
    }

private:
    std::pair<char, int> data;
    HuffmanNode *left;
    HuffmanNode *right;
};