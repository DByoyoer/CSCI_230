#pragma once
#include <string>

const int ALPHABET_SIZE = 26;

class TrieNode
{
public:
    TrieNode() : isEndOfWord(false), count(0)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
        }
    }

    TrieNode *children[26];
    bool isEndOfWord;
    int count;
};

class Trie
{
public:
    Trie(std::string file);
    void insert(const std::string &word);
    int search(const std::string &word); //Returns the number of times the word occurs in the text
    int size() const;                    //Returns the number of unique words stored in a tree
private:
    int n;
    TrieNode *root;
};