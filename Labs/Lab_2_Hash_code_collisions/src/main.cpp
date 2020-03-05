#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void allLowerCase(std::string& word)
{
    for (unsigned int i = 0; i < word.size(); i++)
    {
        word[i] = std::tolower(word[i]);
    }
}

int hashCode(std::string word)
{
    unsigned int x = 0;
    for (unsigned int i = 0; i < word.size(); i++)
    {
        x = (x << 13) | (x >> 19);
        x += (unsigned int)word[i];
    }
    return (int)x;
}

int main()
{
    std::ifstream infile;
    infile.open("usdeclarPC.txt");
    std::string word;
    std::vector<std::string> words;
    while (infile >> word)
    {
        //Removes anything that is not a number or an letter
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char x) { return !std::isalnum(x); }), word.end());
        allLowerCase(word);
        words.push_back(word);
    }
    /*
    TODO: Could probably move this into the file processing loop
    TODO: Skiplist simulation
    */
    std::map<std::string, int> encounteredWords;
    std::map<int, std::string> collisionTest;
    int code = 0;
    int totalCollisions = 0;
    for (std::string w : words)
    {
        if (encounteredWords.find(w) == encounteredWords.end())
        {
            encounteredWords.insert(std::pair<std::string, int>(w, w.size()));
            code = hashCode(w);
            if (collisionTest.find(code) == collisionTest.end())
            {
                collisionTest.insert(std::pair<int, std::string>(code, word));
            }
            else
            {
                totalCollisions++;
            }
        }
    }
    std::cout << words.size() << ' ' << totalCollisions << std::endl;
}