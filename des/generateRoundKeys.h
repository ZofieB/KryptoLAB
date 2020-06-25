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
int getLowerBits(int source, int number);
int getHigherBits(int source, int number, int bitsize);
int shiftLeftCarry(int source, int number);