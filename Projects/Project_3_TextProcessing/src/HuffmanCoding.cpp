#include <fstream>
#include <string>
#include <queue>
#include "HuffmanCoding.hpp"
#include "HuffmanNode.hpp"
//TODO: Figure out how to get newline char without assuming the last newline isn't real

//!TEMP
class Greater
{
public:
    bool operator()(HuffmanNode *a, HuffmanNode *b) const
    {
        return a->frequency() > b->frequency();
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
        //!Only on LF line endings?
        //   text.push_back('\n');
    }
    //removes extra newline
    //text.pop_back();
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

HuffmanNode *HuffmanCoding::buildTree()
{
    buildFreqTable();
    //TODO: Change from pair to node type
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Greater> nodes;
    for (auto p : freqTable)
    {
        nodes.push(new HuffmanNode(p, NULL, NULL));
    }
    HuffmanNode *left;
    HuffmanNode *right;
    int freqSum;
    while (nodes.size() > 1)
    {
        left = nodes.top();
        nodes.pop();
        right = nodes.top();
        nodes.pop();
        freqSum = left->frequency() + right->frequency();

        nodes.push(new HuffmanNode('0', freqSum, left, right));
    }
    HuffmanNode *root = nodes.top();
    nodes.pop();
    return root;
}

void HuffmanCoding::compress()
{
    HuffmanNode *root = buildTree();
}