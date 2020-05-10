#include <fstream>
#include <string>
#include <queue>
#include "HuffmanCoding.hpp"

//!TEMP
class Greater
{
public:
    bool operator()(const std::pair<char, int> &a, const std::pair<char, int> &b) const
    {
        return a.second > b.second;
    }
};

HuffmanCoding::HuffmanCoding(const char *inFile, const char *outFile)
    : inputFileName(inFile), outputFilename(outFile)
{
}

void HuffmanCoding::buildFreqTable()
{
    std::ifstream inFile(inputFileName);
    std::string text;
    std::string temp;
    while (std::getline(inFile, temp))
    {
        text += temp;
        //Have to add a new line since getline doesn't include it
    }
    for (char c : text)
    {
        if (freqTable.count(c))
        {
            freqTable[c]++;
        }
        else
        {
            freqTable[c] = 1;
        }
    }
}

void HuffmanCoding::compress()
{
    buildFreqTable();
    //TODO: Change from pair to node type
    std::priority_queue<pair, std::vector<pair>, Greater>(freqTable.begin(), freqTable.end());
}