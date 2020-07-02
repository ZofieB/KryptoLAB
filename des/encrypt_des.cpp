#include "encrypt_des.h"
#include "generateRoundKeys.h"

int main()
{
    testMakeInputBlocks();
}

vector<string> makeInputBlocks(string &input)
{
    vector<string> inputBlocks;
    //blocklength is 128bit
    int blockChars{128 / (sizeof(char) * 8)};
    int numberOfBlocks{(int) input.size() / blockChars};
    //generate the non-padded blocks
    for(int i = 0; i < numberOfBlocks; i++)
    {
        //create 128-bit long substrings
        inputBlocks.push_back(input.substr( (i * blockChars), blockChars ));
    }
    inputBlocks.push_back( input.substr( numberOfBlocks * blockChars ));
    paddWithZeros( inputBlocks[inputBlocks.size() - 1], 16);
    return inputBlocks;
}

void testMakeInputBlocks()
{
    string str{"abcdefgABCDEFG12347890ieoakjguehnaaaa"};
    vector<string> blocks{makeInputBlocks(str)};
    for(string s : blocks)
    {
        cout << s << "  size:  " << s.length() * 8 << '\n';
    }
}

unsigned long long int getBits(string &s, int offset)
{
    unsigned long long int bits{0};
    //if offset is 0, the left 64 bits are created, with offset=8 the last 64 bits are created
    for(int i = offset; i < s.size() - (8 - offset); i++)
    {
        bits = bits << 8;
        bits = bits | s[i];
    }
    return bits;
}

void paddWithZeros(string &s, int length)
{
    for(int i = (int) s.size(); i < length; i++)
    {
        s.push_back((char) 0);
    }
}

void encryptRound(unsigned long long int right, unsigned long long int left)
{

}

unsigned long long int functionF(unsigned long long int right, unsigned long long int key)
{
    unsigned long long int modifiedRight{0};
    modifiedRight = right ^ key;

}

unsigned long long int sBox(unsigned long long int input, vector<int> sBox)
{
    unsigned int mask{0xff};
    //TODO: Behandlung der Bitfolge in 8 bit chunks --> byte array? 

}