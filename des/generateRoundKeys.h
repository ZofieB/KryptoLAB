#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<bitset>

using namespace std;

void testPermuteKey();
vector<int> cutInputToArray(string &input, const string &delimiter);
string readInput(const string &filename);
unsigned long long int permuteKey(unsigned long long int key, vector<int> permutationTable);
unsigned long long int getLowerBits(unsigned long long int source, int number);
unsigned long long int getHigherBits(unsigned long long int source, int number, int bitsize);
unsigned long long int shiftLeftCarry(unsigned long long int source, int number);
vector<unsigned long long int> generateRoundKeys(unsigned long long int key, int keyNumber, vector<int> permutationTable);