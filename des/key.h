#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<bitset>

using namespace std;

void testPermuteKey();
vector<int> cutInputToArray(string &input, const string &delimiter);
string readInput(const string &filename);
int permuteKey(int key, vector<int> permutationTable);