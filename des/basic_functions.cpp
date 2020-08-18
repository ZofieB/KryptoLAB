#include "basic_functions.h"

vector<int> cutInputToArray(string &input, const string &delimiter)
{
    input.erase(0, 1); //erase [
    input.erase(input.size() - 1, 1); //erase ]
    vector<int> permutationArray;
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        permutationArray.push_back(stoi(token));
        input.erase(0, pos + delimiter.length());
    }
    permutationArray.push_back(stoi(input));
    return permutationArray;
}

string readInput(const string &filename)
{
    //create a String containing the whole text
    ifstream input { filename, std::ios_base::in | std::ios_base::binary };
    char data;
    string inputText;
    while ( input.get(data) )
    {
        inputText.push_back(data);
    }
    return inputText;
}

unsigned long long int getBits(string &s, int offset)
{
    unsigned long long int bits{0};
    //if offset is 0, the left 64 bits are created, with offset=8 the last 64 bits are created
    for(int i = s.size() - (8 - offset) - 1; i >= offset; i++)
    {
        bits = bits << 8;
        bits = bits | s[i];
    }
    return bits;
}

string getBytes(unsigned long long int input, int size)
{
    //size determines how many bytes should be converted from back to front (by default the full input)
    unsigned long long int bitmask{0xff};
    string bytes(size, 0);
    //bring bitmask to starting position
    bitmask = bitmask << ((size - 1) * 8);
    for(int i = 0; i < size; i++)
    {
        //go from the most left byte to the most right so that the bytes are stored in order
        bytes[i] = getHigherBits(input & bitmask, 8, (size - i) * 8);
        bitmask = bitmask >> 8;
    }
    return bytes;
}

unsigned long long int createBitmask(int size)
{
    unsigned long long int bitmask = 1;
    for(int i = 0; i < size - 1; i++)
    {
        bitmask = (bitmask << 1) | 1;
    }
    return bitmask;
}

unsigned long long int getHigherBits(unsigned long long int source, int number, int bitsize)
{
    return source  >> (bitsize - number);
}

void testGetBytes()
{
    unsigned long long int input{0x4142434445464748};
    unsigned long long int input2{0x3132333435363738};

    cout << getBytes(input) << '\n';
    cout << getBytes(input2) << '\n';
}

string bytewiseXOR(const string &a, const string &b)
{
    //only if the string have the same size the functions will work
    if(a.size() == b.size())
    {
        string newString(a);
        for(int i = 0; i < a.size(); i++)
        {
            newString[i] = a[i] ^ b[i];
        }
        return newString;
    }
    return "0"; 
}

