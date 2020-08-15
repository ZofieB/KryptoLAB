#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<bitset>
#include<algorithm>

using namespace std;

vector<string> makeInputBlocks(string &input);
void testMakeInputBlocks();
void paddWithZeros(string &s, int length);

string encryptDESBlock(string &input, vector<unsigned long long int> roundKeys, vector<int> sBoxVector);
vector<string> encryptRound(string right, string left, unsigned long long int key, vector<int> sBoxVector);
string functionF(string right, unsigned long long int key, vector<int> sBoxVector);
string sBox(string input, vector<int> sBoxVector);