#pragma once
#include <map>
#include "HuffmanNode.hpp"

class HuffmanCoding
{
public:
    HuffmanCoding(const char *inFile, const char *outFile);
    void compress();

protected:
    void buildFreqTable();
    HuffmanNode *buildTree();
    typedef std::pair<char, int> pair;
    void getCodes(HuffmanNode *node, std::string prefix,
                  std::map<char, std::string> &output);

private:
    std::map<char, int> freqTable;
    const char *inputFileName;
    const char *outputFilename;
    std::string text;
};