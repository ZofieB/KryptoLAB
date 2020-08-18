#include "encrypt_des.h"
#include "generateRoundKeys.h"
#include "basic_functions.h"

//input arguments shuld be: encrypt/decrypt flag, key, sourcefile, destfile

//encryption is not deterministic
//first character seems to stay the same, last block stays the same (padded?)

int main(int argc, char *argv[])
{
    testDES();
}

string doDES(string &inputfile, unsigned long long int key, vector<int> sBoxVector, vector<int> permutationTable, bool decrypt)
{
    string input{readInput(inputfile)};
    vector<unsigned long long int> roundKeys(generateRoundKeys(key, 16, permutationTable));
    if(decrypt)
    {
        reverse(roundKeys.begin(), roundKeys.end());
    }
    vector<string> inputBlocks{makeInputBlocks(input)};
    string output{""};
    for(string s: inputBlocks)
    {
        output.append(encryptDESBlock(s, roundKeys, sBoxVector));
        //output.append("\t");
    }
    return output;
}

string encryptDESBlock(string &input, vector<unsigned long long int> roundKeys, vector<int> sBoxVector)
{
    //create the splitted substrings
    string right{input.substr(8, 8)};
    string left{input.substr(0, 8)};
    //do the encryption rounds
    //round number is determined by the number of keys, which can be altered
    vector<string> substrings;
    substrings.push_back(left);
    substrings.push_back(right);
    for(int i = 0; i < roundKeys.size(); i++)
    {
        substrings = encryptRound(substrings[1], substrings[0], roundKeys[i], sBoxVector);
    }
    return substrings[0].append(substrings[1]);
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

void paddWithZeros(string &s, int length)
{
    for(int i = (int) s.size(); i < length; i++)
    {
        s.push_back((char) 0);
    }
}

vector<string> encryptRound(string right, string left, unsigned long long int key, vector<int> sBoxVector)
{
    //vector[0] is left value and vector[1] ist right value
    vector<string> newValues(2);
    //old right values becomes new left value
    newValues[0] = right;
    right = functionF(right, key, sBoxVector);
    newValues[1] = bytewiseXOR(right, left);
    return newValues;
}

string functionF(string right, unsigned long long int key, vector<int> sBoxVector)
{
    string byteKey{getBytes(key)};

    string modifiedRight(bytewiseXOR(right, byteKey));
    modifiedRight = sBox(modifiedRight, sBoxVector);
    return modifiedRight;
}

string sBox(string input, vector<int> sBoxVector)
{
    for(int i = 0; i < input.size(); i++)
    {
        input[i] = sBoxVector[input[i]];
    }
    return input;
}

void testDES()
{
    string sBoxString{readInput("sbox.txt")};
    vector<int> sBoxVector{cutInputToArray(sBoxString, ",")};
    string permutationString{readInput("permutation.txt")};
    vector<int> permutationArray{cutInputToArray(permutationString, ", ")};
    string filename{"testfile.txt"};
    string desout{doDES( filename, 0x03fd5c897bc599bc, sBoxVector, permutationArray, false)};
    //cout << desout << endl;
    printStringAsHex(desout);
    ofstream newfile;
    newfile.open("encrypt.txt");
    newfile << desout;
    newfile.close();
    //filename = "encrypt.txt";
    //cout << doDES( filename, 0x03fd5c897bc599bc, sBoxVector, permutationArray, true);
}

/*

4 gleich
4 anders
4 gleich
4 anders
usw


*/