#include"key.h"

//permutation table specifies for each position of the result the position of the input it is taken from

int main()
{
    testPermuteKey();
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
