#include <fstream>
#include <string>
#include <queue>
#include "HuffmanCoding.hpp"
#include "HuffmanNode.hpp"

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

void HuffmanCoding::getCodes(HuffmanNode *node, std::string prefix,
                             std::map<char, std::string> &output)
{
    if (node->isExternal())
    {
        output[node->getChar()] = prefix;
    }
    else
    {
        getCodes(node->getLeft(), prefix + "0", output);
        getCodes(node->getRight(), prefix + "1", output);
    }
}

void HuffmanCoding::compress()
{
    HuffmanNode *root = buildTree();
    std::map<char, std::string> codes;
    getCodes(root, "", codes);
    std::string result;
    std::ofstream outfile(outputFilename);
    for (char c : text)
    {
        result += codes[c];
    }
    for (auto p : codes)
    {
        outfile << p.first << ' ' << p.second << '\n'; //Output the table containing the character codes
    }
    outfile << "\n--------\nNumber of characters: " << root->frequency()
            << "\nNumber of bits: " << result.length() << "\nCompressed: "
            << result;
}