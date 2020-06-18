#include "calc_key.h"
#include "basic_functions.h"

/*int main()
{
    std::cout << "The key ist: " <<  determineKey( readInput("encypted-lorem-4-binary.txt"), 98) << '\n';
    return 0;
}*/

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
