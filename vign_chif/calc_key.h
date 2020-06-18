#include <vector>
#include <string>

std::string determineKey(const std::string &cryptotext, int keylength);
int determineColumnKey(const std::string &column);
std::string getColumn(int columnNumber, int keyLength, const std::string &cryptotext);