#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

std::vector<double> calcICForColumns(int keyLength, const std::string &inputText);
double calcAverageIC(const std::vector<double> &columnIC);
double calcIC(const std::vector<double> &counter, int chunkLength);
void testIC(int chunkLength);
std::vector<int> determineKeyLength(const std::string &inputText, int maxLength);
std::vector<int> primes(int number);