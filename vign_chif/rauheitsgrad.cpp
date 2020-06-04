#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

double calcRauheitsgrad( std::string filename );
std::vector<double> countCharacters( const std::string &input );
void calcFrequencies( std::vector<double> &vec, double allChars );
double calcSquaredSum ( const std::vector<double> &vec );


int main() 
{
    std::vector<std::string> filenames {"random.txt", "lorem.txt", "constant.txt"};
    for(int i = 0; i < filenames.size(); i++)
    {
        double rauheitsgrad { calcRauheitsgrad(filenames[i])};
        std::cout << "The Rauheitsgrad of the file " << filenames[i] << " is: " << rauheitsgrad << '\n'; 
    }
    return 0;
}

double calcRauheitsgrad( std::string filename )
{
    //count the occurences of characters in the file
    std::vector<double> characterOcc { countCharacters( filename ) };
    double rauheitsgrad{0};

    //calculate the frequencies instead of abs values
    double cardAlphNeu = 0;
    double cardAlphabet { static_cast<double>(accumulate( characterOcc.begin(), characterOcc.end(), 0 )) };
    calcFrequencies( characterOcc, cardAlphabet );

    //calculate the sum of the squared frequencies
    rauheitsgrad = calcSquaredSum(characterOcc);

    return rauheitsgrad - ( (double)1 / (double)128);
}

std::vector<double> countCharacters( const std::string &filename )
{
    std::ifstream input { filename };
    std::vector<double> ascii_count( 128 );
    char data{0};
    while ( input.get(data) )
    {
        //increment the counter vector at the position of the read character value
        ascii_count[data] ++;
    }

    return ascii_count;
}

void calcFrequencies( std::vector<double> &vec, double allChars )
{
    for( double &d : vec )
    {
        d = d / allChars;
    }
}

double calcSquaredSum (const std::vector<double> &vec )
{
    double sum{0};
    for ( double d : vec )
    {
        sum = sum + (d * d);
    }
    return sum;
}
