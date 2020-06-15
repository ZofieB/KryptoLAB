#include <vector>
#include <string>

#include "rauheitsgrad_header.h"

//given keylength

//for every column of text seperated by keylength
//test all key possibilities
//calculate rauheitsgrad of decrypted text and compare to that of lorem ipsum
//alternative: chi squared test

std::vector<double> countLoremFrequencies();

int main()
{
    std::vector<double> loremFreq{countLoremFrequencies()};
    for ( int i = 0; i< loremFreq.size(); ++i)
    {
        std::cout << "Frequenz von " << (char) i << " ist: " << loremFreq[i] << '\n';
    }

    return 0;
}

std::string getColumn(int columnNumber, int keyLength, const std::string &cryptotext);
std::string decrypt(std::string cryptotext, int key);
std::vector<double> countLoremFrequencies();

std::string getColumn(int columnNumber, int keyLength, const std::string &cryptotext)
{
    //splits a given text into columns for the desired columns number (starting at 0 for the first column)
    std::string columnOutput;

    for (int j = columnNumber; j < cryptotext.size(); j+= keyLength)
    {
        //add character to output string
        columnOutput.push_back(cryptotext[j]);
    }
    
    return columnOutput;
}

std::string decrypt(const std::string &cryptotext, int key)
{
    std::string decrypted;
    for (char s : cryptotext)
    {
        decrypted.push_back( (s + key) % 128 );
    }
    return decrypted;
}

std::vector<double> countLoremFrequencies()
{
    //calculate Frequency of all Lorem Characters
    std::vector<double> loremFreq {countCharacters("lorem.txt")};
    double cardAlphabet { static_cast<double>(accumulate( loremFreq.begin(), loremFreq.end(), 0 )) };
    calcFrequencies( loremFreq, cardAlphabet );
    return loremFreq;
}

std::vector<double> calcElementwiseError(std::vector<double> v1, std::vector<double> v2)
{
    std::vector<double> error;
    //i assume the two vectors have the same length
    for(int i = 0; i < v1.size(); ++i)
    {
        error.push_back( fabs(v1[i] = v2[i]) );
    }
    return error;
}

std::vector<double> decryptedColumnFrequencies(std::string column)
{
    std::vector<double> asciiCount(128);

    for(int i = 0; i < column.size(); ++i)
    {
        asciiCount[column[i]]++;
    }

    return asciiCount;
}