#include"generateRoundKeys.h"
#include "basic_functions.h"

//permutation table specifies for each position of the result the position of the input it is taken from

int main(int argc, char **argv)
{
    unsigned long long int key{0};
    if( argc == 1)
    {
        key = 0x03fd5c897bc599bc;
    }
    else
    {
        key = stoi(argv[1]);
    }
    string permutationString{readInput("permutation.txt")};
    vector<int> permutationTable{cutInputToArray(permutationString, ", ")};
    vector<unsigned long long int> roundKeys{generateRoundKeys(key, 16, permutationTable)};
    for(int i = 0; i < roundKeys.size(); i++)
    {
        cout << "Round key " << i + 1 << '\n';
        cout << hex << "Hex\t:  " << roundKeys[i] << '\n';
        cout << dec << "Binary\t:  " << bitset<64>(roundKeys[i]) << '\n';
    }
    return 0;
}

unsigned long long int permuteKey(unsigned long long int key, vector<int> permutationTable, int bitsize)
{
    unsigned long long int permutation = 0;
    for ( int i = 0; i < permutationTable.size(); i++ )
    { 
        permutation <<= 1;
        //cout << "Round: " << i << "\tPermutation: " << bitset<64>(permutation) << '\t';
        //cout << "Masked bit: " << bitset<64>(((unsigned long long)1 << (bitsize - 1)) >> permutationTable[i]) << '\n';
        if ( key & (((unsigned long long)1 << (bitsize - 1)) >> permutationTable[i]) )
            permutation |= 1;
    }

    return permutation;
}
unsigned long long int getLowerBits(unsigned long long int source, int number)
{
    int bitmask = 1;
    for(int i = 0; i < number - 1; i++)
    {
        bitmask = (bitmask << 1) | 1;
    }
    return source & bitmask;
}

unsigned long long int getHigherBits(unsigned long long int source, int number, int bitsize)
{
    return source  >> (bitsize - number);
}

unsigned long long int shiftLeftCarry(unsigned long long int source, int number, int bitsize)
{
    unsigned long long int shifted{ source << number };
    unsigned long long int carry{ source >> (bitsize - number)};

    return shifted | carry;
}
vector<unsigned long long int> generateRoundKeys(unsigned long long int key, int keyNumber, vector<int> permutationTable)
{
    vector<unsigned long long int> roundKeys(keyNumber);
    unsigned long long int lowerBits{getLowerBits(key, 32)};
    unsigned long long int higherBits{getHigherBits(key, 32, 64)};
    for(int i = 0; i < keyNumber; i++)
    {
        lowerBits = shiftLeftCarry(lowerBits, 2, 32);
        higherBits = shiftLeftCarry(higherBits, 2, 32);
        roundKeys[i] = permuteKey( (lowerBits | (higherBits << 32)) , permutationTable, 64);
    }
    return roundKeys;
}


//testsection
void testInputandCut()
{
    string input{readInput("permutation.txt")};
    vector<int> permutationArray{cutInputToArray(input, ", ")};
    for(int i : permutationArray)
    {
        cout << i << '\n';
    }
}
void testPermuteKey()
{
    vector<int> permutationTable{3, 6, 0, 2, 4, 1, 7, 5};
    unsigned long long int key = 154;
    // key : 10011010       128 + 16 + 8 + 2 = 154
    // permutation: 1110 1000
    // permutation from behind: 10001110
    unsigned long long int permutation{permuteKey(key, permutationTable, 8)};
    cout << bitset<8>(key) << " is permutet to " << bitset<8>(permutation);
}
