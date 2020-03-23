#include <iostream>
#include "Entry.hpp"
#include "HashCode.hpp"
#include "HashMap.hpp"
#include <fstream>
#include <vector>
#include <string>

struct RecordData
{
    int population;
    std::string name;
    RecordData(int n = 0, std::string s = "") : population(n), name(s) {}
};

std::vector<Entry<int, RecordData>> processFile(std::string filePath)
{
    std::vector<Entry<int, RecordData>> entryList;
    Entry<int, RecordData> inputEntry;
    std::ifstream inputFile;
    inputFile.open(filePath);
    int size;
    inputFile >> size;
    std::string stateCode, population, name;
    for (int i = 0; i < size; i++)
    {
        std::getline(inputFile, stateCode, ',');
        std::getline(inputFile, population, ',');
        std::getline(inputFile, name);
        inputEntry.setKey(std::stoi(stateCode));
        inputEntry.setValue(RecordData(std::stoi(population), name));
        entryList.push_back(inputEntry);
    }
    return entryList;
}

int main()
{
    std::string filepath;
    HashMap<int, RecordData, HashCode> *populationDataTable;
    std::vector<Entry<int, RecordData>> entryList;
    std::cout << "Please enter the file path for the input file you wish to use.\n";
    std::cin >> filepath;
    entryList = processFile(filepath);
    if (entryList.empty())
    {
        std::cout << "File not found or file is empty.";
        return -1;
    }
    int choice;
    double loadFactor;
    std::cout << "1. Chain Hashing\n"
              << "2. Linear Probe Hashing\n"
              << "3. Double Hashing\n"
              << "Please choose a hashing scheme: ";
    std::cin >> choice;
    std::cout << "\n Please enter a load factor between 0-1: ";
    std::cin >> loadFactor;
    switch (choice)
    {
    case 1:
        populationDataTable = new ChainHashMap<int, RecordData, HashCode>(entryList, loadFactor);
    case 2:
    case 3:
        break;

    default:
        break;
    }
}