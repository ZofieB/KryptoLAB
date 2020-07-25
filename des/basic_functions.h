#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<bitset>

using namespace std;

vector<int> cutInputToArray(string &input, const string &delimiter);
string readInput(const string &filename);
unsigned long long int getBits(string &s, int offset);
string getBytes(unsigned long long int input, int size = 8);
void testGetBytes();
unsigned long long int createBitmask(int size);
unsigned long long int getHigherBits(unsigned long long int source, int number, int bitsize);
string bytewiseXOR(const string &a, const string &b);