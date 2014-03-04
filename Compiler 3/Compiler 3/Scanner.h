#include <sstream>

class Token;

class Scanner
{
	Token *Scan(std::stringstream &stream);
};