#include "HashCode.hpp"
#include "HashMap.hpp"
#include "OpenAddressMap.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct RecordData
{
    int population;
    std::string name;
    RecordData(int n = 0, std::string s = "") : population(n), name(s) {}
    friend std::ostream &operator<<(std::ostream &os, const RecordData &data)
    {
        os << data.population << ' ' << data.name;
        return os;
    }
};

//returns number of the choice
int menu()
{
    std::cout << "\n1. Search for a record\n"
              << "2. Insert a record\n"
              << "3. Delete a record\n"
              << "4. List all records\n"
              << "5. Exit\n\n"
              << "Please Select an option: ";
    int choice;
    std::cin >> choice;
    std::cout << choice << std::endl; //!Alert delete later
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return 0;
    }
    return choice;
}

std::vector<Entry<int, RecordData>> processFile(std::string filePath)
{
    std::vector<Entry<int, RecordData>> entryList;
    Entry<int, RecordData> inputEntry;
    std::ifstream inputFile;
    inputFile.open(filePath);
    if (inputFile.fail())
    {
        return entryList;
    }
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
    std::vector<Entry<int, RecordData>> entryList;
    std::cout << "Please enter the file path for the input file you wish to use:\n";
    std::cin >> filepath;
    std::cout << filepath << std::endl; //!Alert: Delete later
    entryList = processFile(filepath);
    if (entryList.empty())
    {
        std::cout << "File not found or file is empty.";
        return -1;
    }

    int code, population;
    std::string name;
    int choice;
    double loadFactor;
    std::cout << "\n1. Chain Hashing\n"
              << "2. Linear Probe Hashing\n"
              << "3. Double Hashing\n"
              << "Please choose a hashing scheme: ";
    std::cin >> choice;
    std::cout << choice << std::endl; //!Alert: Delete later
    std::cout << "\nPlease enter a load factor between 0-1: ";
    std::cin >> loadFactor;
    std::cout << loadFactor << std::endl; //!Alert: Deletle later
    ChainHashMap<int, RecordData, HashCode> table(entryList, loadFactor);
    int operation = 0;
    if (choice == 1)
    {
        while (operation != 5)
        {
            operation = menu();
            switch (operation)
            {
            case 1:
            {
                std::cout << "Please enter the state code: ";
                std::cin >> code;
                std::cout << code << std::endl; //!ALERT: For file redirection delete later
                auto it = table.find(code, true);
                if (it == table.end())
                {
                    std::cout << "Could not find the record\n";
                }
                else
                {
                    std::cout << "Record Found\n";
                    std::cout << (*it).value() << '\n';
                }
            }
            break;
            case 2:
            {
                std::cout << "Please enter the state code, population and name separated by spaces:\n";
                std::cin >> code >> population;
                std::getline(std::cin, name);
                std::cout << code << " " << population << " " << name << std::endl; //!Alert: Delete later
                table.put(code, RecordData(population, name), true);
            }
            break;
            case 3:
            {
                std::cout << "Please enter the state code: ";
                std::cin >> code;
                std::cout << code << std::endl; //!Alert: Delete later
                table.erase(code, true);
            }
            break;
            case 4:
            {
                table.printAll();
            }
            break;
            default:
                break;
            }
        }
    }
    else
    {
        OpenAddressMap<int, RecordData, HashCode> *table2;
        if (choice == 2)
        {
            table2 = new OpenAddressMap<int, RecordData, HashCode>(entryList, loadFactor);
        }
        else
        {
            table2 = new DoubleHashMap<int, RecordData, HashCode>(entryList, loadFactor);
        }
        while (operation != 5)
        {
            operation = menu();
            switch (operation)
            {
            case 1:
            {
                std::cout << "Please enter the state code: ";
                std::cin >> code;
                std::cout << code << std::endl; //!Alert: Delete later
                auto it = table2->find(code, true);
                if (it == table2->end())
                {
                    std::cout << "Could not find the record\n";
                }
                else
                {
                    std::cout << (*it).value() << '\n';
                }
            }
            break;
            case 2:
            {
                std::cout << "Please enter the state code, population and name separated by spaces:\n";
                std::cin >> code >> population;
                std::getline(std::cin, name);
                std::cout << code << " " << population << " " << name << std::endl; //!Alert: Delete later
                table2->put(code, RecordData(population, name), true);
            }
            break;
            case 3:
            {
                std::cout << "Please enter the state code: ";
                std::cin >> code;
                std::cout << code << std::endl; //!Alert: Delete later
                table2->erase(code, true);
            }
            break;
            case 4:
            {
                table2->printAll();
            }
            break;
            default:
                break;
            }
        }
    }
}
