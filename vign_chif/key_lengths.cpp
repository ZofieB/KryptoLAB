#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

std::string readInput(const std::string &filename);
void testReadInput(const std::string &filename);

std::vector<double> calcICForColumns(int keyLength, const std::string &inputText);

double calcAverageIC(const std::vector<double> &columnIC);

double calcIC(const std::vector<double> &counter, int chunkLength);
void testIC(int chunkLength);

int maxElementsIndex(const std::vector<double> &v);

std::vector<int> determineKeyLength(const std::string &filename, int maxLength);

std::vector<int> primes(int number);


int main()
{
    std::vector<std::string> filenames {"encypted-lorem-1-binary.txt", "encypted-lorem-2-binary.txt", "encypted-lorem-3-binary.txt", "encypted-lorem-4-binary.txt"};
    for (std::string s : filenames)
    {
        std::vector<int> primeNumbers {determineKeyLength(s, 100)};

        std::cout << "Possible blocklengths are (including multiples and factors of those): \n";

        for (int i : primeNumbers)
            std::cout << i << '\t';
            std::cout << std::endl << std::endl;
    }
    //std::cout << determineKeyLength("encypted-lorem-4-binary.txt", 100) << '\n';

    //testReadInput("encypted-lorem-2-binary.txt");
    return 0;
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
void testReadInput(const std::string &filename)
{
    std::string inputText{readInput(filename)};
    int stringSize{ (int) inputText.size()};
    std::cout << inputText;
}

std::vector<double> calcICForColumns(int keyLength, const std::string &inputText)
{
    int textLength{ (int) inputText.size() };

    std::vector<double> columnIC;
    int columnSize{ (int) inputText.size() / keyLength };

    //loop for every column, where number of columns is keySize
    for(int i = 0; i < keyLength; ++i)
    {
        //both loops together touch every element exactly once, but make handling it easier
        std::vector<double> ascii_count( 128 );         //creates new vector for every iteration of outer loop
        for (int j = i; j < inputText.size(); j+= keyLength)
        {
            //count absolute frequencies
            ascii_count[inputText[j]] ++;
        }
        columnIC.push_back( calcIC(ascii_count, columnSize) );
    }

    return columnIC;
}

double calcAverageIC(const std::vector<double> &columnIC)
{
    double sum{0};
    for(double d : columnIC)
    {
        sum += d;
    }
    return (sum / (double) columnIC.size());
}

double calcIC(const std::vector<double> &counter, int columnSize)
{
    double ic{0};
    for ( double d : counter)
    {
        ic += d * ( d - 1 ); 
    }

    ic = ic * ( 1 / ( (double )columnSize * ( (double) columnSize - 1 ) ) );
    return ic;
}
void testIC(int chunkLength)
{
    std::vector<double> testVector(10);
    for(int i = 0; i < 10; i++)
    {
        testVector[i] = i + 1;
    } 
    std::cout << calcIC(testVector, chunkLength) << '\n';
}

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

std::vector<int> determineKeyLength(const std::string &filename, int maxLength)
{
    std::string inputText{readInput(filename)};
    std::vector<double> averageIC;

//start with i = 2 to prevent dividing by 0
    for( int i = 1; i < maxLength; i++)
    {
        std::vector<double> columnIC{ calcICForColumns(i, inputText) };
        averageIC.push_back( calcAverageIC(columnIC) );
    }
    //Indexing starts at 2, as the first entry in avergae IC is for keyLength 2
    int maxIndex{ maxElementsIndex(averageIC) + 1 };
    
    return primes(maxIndex);
}

std::vector<int> primes(int number)
{
    std::vector<int> primes;
    int anz{0};
    for ( int i =2; i <= number ; i ++)
    {
        while ( number % i == 0)
        {
            primes.push_back(i);
            number /= i ;
        }
    }
    return primes;
}