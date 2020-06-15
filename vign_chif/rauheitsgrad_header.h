#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

double calcRauheitsgrad( std::string filename );
std::vector<double> countCharacters( const std::string &input );
void calcFrequencies( std::vector<double> &vec, double allChars );
double calcSquaredSum ( const std::vector<double> &vec );
int maxElementsIndex(const std::vector<double> &v);