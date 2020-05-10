#pragma once
#include <map>

class HuffmanCoding
{
public:
    HuffmanCoding(const char *inFile, const char *outFile);
    void compress();

protected:
    void buildFreqTable();
    typedef std::pair<char, int> pair;

private:
    std::map<char, int> freqTable;
    const char *inputFileName;
    const char *outputFilename;
};