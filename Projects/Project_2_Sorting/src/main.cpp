#include <vector>
#include <iostream>
#include <fstream>
#include "Sorting.hpp"
#include "Comparators.hpp"

void loadFile(const char path[], std::vector<int> &S)
{
    std::ifstream infile;
    infile.open(path);
    int temp;
    if (infile.fail())
    {
        std::cout << "Couldn't find " << path;
        return;
    }
    while (true)
    {
        if (infile.eof())
        {
            break;
        }
        infile >> temp;
        S.push_back(temp);
    }
    infile.close();
}

int main()
{
    std::vector<int> test;
    loadFile("docs/large100k.txt", test);
    std::ofstream outfile;
    outfile.open("docs/test.txt", std::ios_base::app);
    LowToHigh<int> less;
    Sorting<int, LowToHigh<int>> sorter;
    sorter.quickSortMedOf3(test, outfile);
}
