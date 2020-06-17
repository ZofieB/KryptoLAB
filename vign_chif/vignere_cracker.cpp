#include <prototypes.h>

int main(int argc, char **argv)
{
    // first argument after the command is the name of the cryptotext file
    std::string cryptotext{readInput(argv[1])};
    int maxKeylength;

    if(argc == 2)
    {
        maxKeylength = 100;
    }
    else
    {
        //maxKeylength = argv[2]; TODO
    }
    

    std::vector<int> possibleKeylengths{ determineKeyLength(cryptotext, maxKeylength) };
    
    while(true)
    {
        //test every possible keylength combination
    }
}