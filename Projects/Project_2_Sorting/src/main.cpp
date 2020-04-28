#include <vector>
#include <iostream>
#include <string>
#include "Entry.hpp"
#include <fstream>
#include "Sorting.hpp"
#include "Comparators.hpp"

void loadFileIntKey(const char path[], std::vector<Entry<int, std::string>> &S);
void loadFileStringKey(const char path[], std::vector<Entry<std::string, int>> &S);

int main()
{
    typedef Entry<int, std::string> intEntry;
    typedef Entry<std::string, int> stringEntry;

    std::vector<intEntry> unsortedIntKeySmall;
    std::vector<stringEntry> unsortedStringKeySmall;
    std::vector<intEntry> unsortedIntKeyLarge;
    std::vector<stringEntry> unsortedStringKeyLarge;

    //Creating the different lists that need to be sorted

    loadFileIntKey("docs/large100k.txt", unsortedIntKeyLarge);
    loadFileIntKey("docs/small1k.txt", unsortedIntKeySmall);
    loadFileStringKey("docs/large100k.txt", unsortedStringKeyLarge);
    loadFileStringKey("docs/small1k.txt", unsortedStringKeySmall);

    //Copying the unsorted lists into different vectors to test different sorting algs
    //Probaly could have been done better.
    auto intInsertion = unsortedIntKeySmall;
    auto stringInsertion = unsortedStringKeySmall;
    auto intQuickMed3Large = unsortedIntKeyLarge;
    auto intQuickEndLarge = unsortedIntKeyLarge;
    auto stringQuickMed3Large = unsortedStringKeyLarge;
    auto stringQuickEndLarge = unsortedStringKeyLarge;
    auto intQuickMed3Small = unsortedIntKeySmall;
    auto intQuickEndSmall = unsortedIntKeySmall;
    auto stringQuickMed3Small = unsortedStringKeySmall;
    auto stringQuickEndSmall = unsortedStringKeySmall;
    auto intMergeSortLarge = unsortedIntKeyLarge;
    auto intMergeSortSmall = unsortedIntKeySmall;
    auto stringMergeSortLarge = unsortedStringKeyLarge;
    auto stringMergeSortSmall = unsortedStringKeySmall;
    auto intShellSmall = unsortedIntKeySmall;
    auto intShellLarge = unsortedIntKeyLarge;
    auto stringShellSmall = unsortedStringKeySmall;
    auto stringShellLarge = unsortedStringKeyLarge;
    auto intRadixSmall = unsortedIntKeySmall;
    auto intRadixLarge = unsortedIntKeyLarge;

    std::ofstream intOutput, stringOutput;
    intOutput.open("docs/intResults.txt");
    stringOutput.open("docs/stringResults.txt");

    Sorting<intEntry, EntryCompare<intEntry>> intSorter;
    Sorting<stringEntry, EntryCompare<stringEntry>> stringSorter;

    intOutput << "Integer Keys\n\n\n";

    intSorter.insertionSort(intInsertion, intOutput);
    intSorter.quickSortEnd(intQuickEndSmall, intOutput);
    intSorter.quickSortMedOf3(intQuickMed3Small, intOutput);
    intSorter.mergeSort(intMergeSortSmall, intOutput);
    intSorter.radixSort(intRadixSmall, intOutput);
    intSorter.shellSort(intShellSmall, intOutput);

    intSorter.quickSortEnd(intQuickEndLarge, intOutput);
    intSorter.quickSortMedOf3(intQuickMed3Large, intOutput);
    intSorter.mergeSort(intMergeSortLarge, intOutput);
    intSorter.radixSort(intRadixLarge, intOutput);
    intSorter.shellSort(intShellLarge, intOutput);

    stringOutput << "STRING KEYS\n\n\n";

    stringSorter.insertionSort(stringInsertion, stringOutput);
    stringSorter.quickSortEnd(stringQuickEndSmall, stringOutput);
    stringSorter.quickSortMedOf3(stringQuickMed3Small, stringOutput);
    stringSorter.mergeSort(stringMergeSortSmall, stringOutput);
    stringSorter.shellSort(stringShellSmall, stringOutput);
    stringSorter.quickSortEnd(stringQuickEndLarge, stringOutput);
    stringSorter.quickSortMedOf3(stringQuickMed3Large, stringOutput);
    stringSorter.mergeSort(stringMergeSortLarge, stringOutput);
    stringSorter.shellSort(stringShellLarge, stringOutput);
}

void loadFileIntKey(const char path[], std::vector<Entry<int, std::string>> &S)
{
    std::ifstream infile;
    infile.open(path);
    Entry<int, std::string> temp;
    int tempInt;
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
        infile >> tempInt;
        temp.setKey(tempInt);
        temp.setValue(std::to_string(tempInt));
        S.push_back(temp);
    }
    infile.close();
}

void loadFileStringKey(const char path[], std::vector<Entry<std::string, int>> &S)
{
    std::ifstream infile;
    infile.open(path);
    Entry<std::string, int> temp;
    int tempInt;
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
        infile >> tempInt;
        temp.setKey(std::to_string(tempInt));
        temp.setValue(tempInt);
        S.push_back(temp);
    }
    infile.close();
}