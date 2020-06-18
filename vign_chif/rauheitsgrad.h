#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

double calcRauheitsgrad( const std::string &text );
std::vector<double> countInputCharacters( const std::string &input );
void calcFrequencies( std::vector<double> &vec, double allChars );
double calcSquaredSum ( const std::vector<double> &vec );