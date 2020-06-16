#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

double calcRauheitsgrad( std::string filename );
std::vector<double> countInputCharacters( const std::string &input );
void calcFrequencies( std::vector<double> &vec, double allChars );
double calcSquaredSum ( const std::vector<double> &vec );
int maxElementsIndex(const std::vector<double> &v);


/*int main() 
{
    std::vector<std::string> filenames {"random.txt", "lorem.txt", "constant.txt"};
    for(int i = 0; i < filenames.size(); i++)
    {
        double rauheitsgrad { calcRauheitsgrad(filenames[i])};
        std::cout << "The Rauheitsgrad of the file " << filenames[i] << " is: " << rauheitsgrad << '\n'; 
    }

    std::vector<double> chars{countCharacters("lorem.txt")};

    int maxChar{maxElementsIndex(chars)};

    std::cout << "Most common character in Lorem Ipsum is: " << maxChar <<  " /  \"" << (char)maxChar << '\"' << '\n'; 
    return 0;
}*/

double calcRauheitsgrad( std::string filename )
{
    //count the occurences of characters in the file
    std::vector<double> characterOcc { countInputCharacters( filename ) };
    double rauheitsgrad{0};

    //calculate the frequencies instead of abs values
    double cardAlphabet { static_cast<double>(accumulate( characterOcc.begin(), characterOcc.end(), 0 )) };
    calcFrequencies( characterOcc, cardAlphabet );

    //calculate the sum of the squared frequencies
    rauheitsgrad = calcSquaredSum(characterOcc);

    return rauheitsgrad - ( (double)1 / (double)128);
}

std::vector<double> countInputCharacters( const std::string &filename )
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
