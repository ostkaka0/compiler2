#pragma once

#include <vector>
#include <fstream>

class Token;

class Scanner
{
	bool isAlpha(char c);
	bool isDigit(char c);
	bool isSpace(char c);
public:
	std::vector<Token*> Scan(std::ifstream &stream);
};