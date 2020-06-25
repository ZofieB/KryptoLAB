#include"generateRoundKeys.h"

//permutation table specifies for each position of the result the position of the input it is taken from

int main(int argc, char **argv)
{
    int key{0};
    if( argc == 1)
    {
        key = 493827;
    }
    else
    {
        key = stoi(argv[1]);
    }
    string permutationString{readInput("permutation.txt")};
    vector<int> permutationTable{cutInputToArray(permutationString, ", ")};
    vector<int> roundKeys{generateRoundKeys(key, 16, permutationTable)};
    for(int i : roundKeys)
    {
        cout << i << '\n';
    }
    return 0;
}

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
    ifstream input { filename };
    char data;
    string inputText;
    while ( input.get(data) )
    {
        inputText.push_back(data);
    }
    return inputText;
}

int permuteKey(int key, vector<int> permutationTable, int bitsize)
{
    int permutation = 0;
    for ( int i = 0; i < permutationTable.size(); i++ )
    { 
        permutation <<= 1;
        //cout << "Round: " << i << "\tPermutation: " << bitset<8>(permutation) << '\t';
        //cout << "Masked bit: " << bitset<8>((1 << (bitsize - 1)) >> permutationTable[i]) << '\n';
        if ( key & ((1 << (bitsize - 1)) >> permutationTable[i]) )
            permutation |= 1;
    }

    return permutation;
}
int getLowerBits(int source, int number)
{
    int bitmask = 1;
    for(int i = 0; i < number - 1; i++)
    {
        bitmask = (bitmask << 1) | 1;
    }
    return source & bitmask;
}

int getHigherBits(int source, int number, int bitsize)
{
    return source  >> (bitsize - number);
}

int shiftLeftCarry(int source, int number, int bitsize)
{
    int shifted{ source << number };
    int carry{ source >> (bitsize - number)};

    return shifted | carry;
}
vector<int> generateRoundKeys(int key, int keyNumber, vector<int> permutationTable)
{
    vector<int> roundKeys(keyNumber);
    int lowerBits{getLowerBits(key, 32)};
    int higherBits{getHigherBits(key, 32, 64)};
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
    int key = 154;
    // key : 10011010       128 + 16 + 8 + 2 = 154
    // permutation: 1110 1000
    // permutation from behind: 10001110
    int permutation{permuteKey(key, permutationTable, 8)};
    cout << bitset<8>(key) << " is permutet to " << bitset<8>(permutation);
}
