#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "HuffmanCoding.hpp"
#include "Trie.hpp"

int main()
{
    HuffmanCoding test("docs/moneyIn.txt", "docs/moneyOut.txt");
    test.compress();
    Trie declaration("docs/usdeclarPC.txt");
    std::string searchTerms[]{"honor", "honour", "government", "computer", "the"};
    int occurences = 0;
    std::cout << "There are " << declaration.size() << " words in the trie\n";
    for (std::string s : searchTerms)
    {
        occurences = declaration.search(s);
        std::cout << s << " occurs " << occurences << " times in the input file.\n";
    }
}