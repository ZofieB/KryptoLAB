#include "basic_functions.h"

int maxElementsIndex(const std::vector<double> &v)
{
    double maxElement{0};
    int maxIndex{0};
    for (int i = 0; i < v.size(); i++)
    {
        if(v[i] > maxElement)
        {
            maxElement = v[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

std::string readInput(const std::string &filename)
{
    //create a String containing the whole text
    std::ifstream input { filename , std::ios_base::in | std::ios_base::binary };
    char data;
    std::string inputText;
    while ( input.get(data) )
    {
        inputText.push_back(data);
    }
    return inputText;
}

std::vector<double> countCharacters(const std::string &s)
{
    std::vector<double> charCount(128);
    for(char c : s)
    {
        charCount[c]++;
    }
    return charCount;
}

std::string decrypt(const std::string &cryptotext, const std::string &key)
{
    std::string plaintext;
    for( int i = 0; i < cryptotext.size(); i+= key.size())
    {
        for(int j = 0; j < key.size(); j++)
        {
            plaintext.push_back( ( (cryptotext[i + j] - key[j]) + 128 ) % 128 );
        }
    }
    return plaintext;
}
