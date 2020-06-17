#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

//calc key
std::string readInput(const std::string &filename);
std::string determineKey(const std::string &cryptotext, int keylength);
int determineColumnKey(const std::string &column);
std::string getColumn(int columnNumber, int keyLength, const std::string &cryptotext);
std::vector<double> countCharacters(const std::string &s);

//rauheitsgrad
double calcRauheitsgrad( std::string filename );
std::vector<double> countInputCharacters( const std::string &input );
void calcFrequencies( std::vector<double> &vec, double allChars );
double calcSquaredSum ( const std::vector<double> &vec );
int maxElementsIndex(const std::vector<double> &v);

//keylengths
std::vector<double> calcICForColumns(int keyLength, const std::string &inputText);
double calcAverageIC(const std::vector<double> &columnIC);
double calcIC(const std::vector<double> &counter, int chunkLength);
int maxElementsIndex(const std::vector<double> &v);
std::vector<int> determineKeyLength(const std::string &filename, int maxLength);
std::vector<int> primes(int number);