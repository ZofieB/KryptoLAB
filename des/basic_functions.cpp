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
    ifstream input { filename };
    char data;
    string inputText;
    while ( input.get(data) )
    {
        inputText.push_back(data);
    }
    return inputText;
}