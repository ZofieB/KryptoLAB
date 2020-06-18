#include <vector>
#include <algorithm>
#include <math.h>

#include "basic_functions.h"
#include "rauheitsgrad.h"
#include "key_lengths.h"
#include "calc_key.h"

std::vector<int> combination;

void combinations(std::vector<int> &finalCombs, const std::vector<int> &numbers, int offset, int k);

int main(int argc, char **argv)
{
    // first argument after the command is the name of the cryptotext file
    std::string cryptotext{readInput(argv[1])};
    int maxKeylength{0};

    if(argc == 2)
    {
        maxKeylength = 100;
    }
    else if(argc == 3)
    {
        maxKeylength = std::stoi(argv[2], nullptr, 10); 
    }
    else
    {
        std::cout << "Es wurde nicht die korrekte Anzahl an Argumenten eingegeben!\n";
    }

    std::vector<int> possibleKeylengths{ determineKeyLength(cryptotext, maxKeylength) };
    
    //coumpute all possible product combinations for the given primes of the keylength
    std::vector<int> finalKeyLengths;
    for (int i = 1; i <= possibleKeylengths.size() ; i++)
    {
        combinations(finalKeyLengths, possibleKeylengths, 0, i);
    }
    //compute for every possible Keylength the key, decrypt the text and compare rauheitsgrad

    double loremRauheitsgrad{ calcRauheitsgrad( readInput("lorem.txt") ) };
    //find the minimum difference to rauheitsgrad

    std::string plaintext;
    std::string key;
    //rauheitsgrad is always < 1 as is the difference to another one
    double minRauheitsDiff{1};
    int j;
    for ( int i = 0; i < finalKeyLengths.size(); i++)
    {
        std::string tempKey{ determineKey(cryptotext, finalKeyLengths[i]) };
        std::string decrypted{ decrypt(cryptotext, tempKey) };
        if( fabs(calcRauheitsgrad(decrypted) - loremRauheitsgrad) < minRauheitsDiff )
        {
            plaintext = decrypted;
            key = tempKey;
            j = i;
        }
    }

    std::cout<< "Plaintext: \n" << plaintext << std::endl;
    std::cout << "Used key: " << key << '\n';
    return 0;
}

void combinations(std::vector<int> &finalCombs, const std::vector<int> &numbers, int offset, int k)
{
    if (k == 0) 
    {
        int product{1};
        for(int i : combination)
        {
            product = product * i;
        }
        if(std::find(finalCombs.begin(), finalCombs.end(), product) == finalCombs.end())
        {
            finalCombs.push_back(product);
        }
        return;
    }
    for (int i = offset; i <= numbers.size() - k; ++i) 
    {
        combination.push_back(numbers[i]);
        combinations(finalCombs, numbers, i+1, k-1);
        combination.pop_back();
    }
}