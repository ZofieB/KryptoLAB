#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<bitset>

using namespace std;

vector<string> makeInputBlocks(string &input);
void testMakeInputBlocks();
void paddWithZeros(string &s, int length);

vector<string> encryptRound(string right, string left, unsigned long long int key, vector<int> sBoxVector);
string functionF(string right, unsigned long long int key, vector<int> sBoxVector);
string sBox(string input, vector<int> sBoxVector);