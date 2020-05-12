#include "Trie.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

Trie::Trie(std::string file) : n(0), root(new TrieNode())
{
    std::ifstream infile(file);
    std::string word;
    while (infile >> word)
    {
        //Removes anything that is not a letter from the word
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
        //If the word was just a number don't add the empty string to the trie
        if (word.length() == 0)
        {
            continue;
        }
        for (int i = 0; i < word.length(); i++)
        {
            word[i] = std::tolower(word[i]);
        }
        insert(word);
    }
}

int Trie::size() const
{
    return n;
}

void Trie::insert(const std::string &word)
{
    TrieNode *node = root;
    int index = 0;
    for (char c : word)
    {
        index = c - 'a';
        if (node->children[index] == NULL)
        {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }

    if (!(node->isEndOfWord))
    {
        node->isEndOfWord = true;
        n++;
    }
    node->count++;
}

int Trie::search(const std::string &word)
{
    TrieNode *node = root;
    int index = 0;
    for (char c : word)
    {
        index = c - 'a';
        if (node->children[index] == NULL)
        {
            return 0;
        }
        node = node->children[index];
    }
    return node->count;
}