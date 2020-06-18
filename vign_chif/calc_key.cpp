#include <vector>
#include <string>
#include<math.h>

#include "rauheitsgrad.h"

//using double vectors for compatibility

std::string getColumn(int columnNumber, int keyLength, const std::string &cryptotext);
std::string decrypt(const std::string &cryptotext, int key);
std::vector<double> countLoremFrequencies();
std::vector<double> calcElementwiseError(std::vector<double> v1, std::vector<double> v2);
std::vector<double> decryptedColumnFrequencies(std::string column, int key);
double calcSquaredErrorOfFrequencies(std::vector<double> frequenciesColumn);
void testSquaredErrorOfFrequencies();
int determineKeyForColumn(const std::string &column);
int determineColumnKey(const std::string &column);
std::string determineKey(const std::string &cryptotext, int keylength);
std::string readInput(const std::string &filename);
std::vector<double> countCharacters(const std::string &s);
void testCountCharacters();

/*int main()
{
    std::cout << "The key ist: " <<  determineKey( readInput("encypted-lorem-4-binary.txt"), 98) << '\n';
    return 0;
}*/

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
        decrypted.push_back( ((s - key) + 128 )% 128 );
    }
    return decrypted;
}

std::vector<double> countLoremFrequencies()
{
    //calculate Frequency of all Lorem Characters
    std::vector<double> loremFreq {countInputCharacters("lorem.txt")};
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
        error.push_back( fabs(v1[i] - v2[i]) );
    }
    return error;
}

std::vector<double> decryptedColumnFrequencies(std::string column, int key)
{
    column = decrypt(column, key);
    std::vector<double> asciiCount{countCharacters(column)};
    double cardColumn { static_cast<double>(accumulate( column.begin(), column.end(), 0 )) };
    calcFrequencies(asciiCount, cardColumn);

    return asciiCount;
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

void testCountCharacters()
{
    std::string s = "AABBCCCDDDGGJK";
    std::vector<double> chars{countCharacters(s)};
    for(int i = 0; i < 128; i++)
    {
        std::cout << "Anzahl von " << (char) i << "\'s ist: " << chars[i] << '\n';
    }
}

double calcSquaredErrorOfFrequencies(std::vector<double> frequenciesColumn)
{
    std::vector<double> errorVector{calcElementwiseError(frequenciesColumn, countLoremFrequencies())};
    double squaredError{calcSquaredSum(errorVector)};
    return squaredError;
}

void testSquaredErrorOfFrequencies()
{
    std::cout << calcSquaredErrorOfFrequencies(countLoremFrequencies()) << '\n';

    std::vector<double> lorem{countLoremFrequencies()};
    lorem[75]+=0.5;
    std::cout << calcSquaredErrorOfFrequencies(lorem) << '\n';
}

int determineKeyForColumn(const std::string &column)
{
    //OLD METHOD
    //test every possible key as ASCII Character by determining the minimum squared error
    double min{128};          //every error is <1, so 128 * 1 can be the initial minimum value (if every error is 1 we get 128, as we sum the errors)
    int key{0};
    for(int i = 65; i <91; i++)
    {
        std::vector<double> decColumnFreq{decryptedColumnFrequencies(column, i)};
        double squaredError{calcSquaredErrorOfFrequencies(decColumnFreq)};
        if( squaredError < min)
        {
            min = squaredError;
            key = i;
        }
    }
    return key;
}

int determineColumnKey(const std::string &column)
{
    //NEW METHOD
    int max{0};     //holds the maximum count
    int maxChar{0}; //holds the corresponding character
    //count the chars in the given column
    std::vector<double> numberCharacters{countCharacters(column)};
    for(int i = 0; i < 128; i++)
    {
        if(numberCharacters[i] > max)
        {
            max = (int) numberCharacters[i];
            maxChar = i;
        }
    }

    return ((( maxChar - 32 ) % 128) + 128) % 128;

}

std::string determineKey(const std::string &cryptotext, int keylength)
{
    std::string key;
    //do something for every column
    for(int i = 0; i < keylength; i++)
    {
        std::string column{getColumn(i, keylength, cryptotext)};
        int colKey{determineColumnKey(column)};
        key.push_back((char) colKey);
    }
    return key;
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