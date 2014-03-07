#include "Scanner.h"
#include "Tokens.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool Scanner::isAlpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	else if (c >= 'A' && c  <= 'Z')
		return true;
	else if (c == '_')
		return false;

	return false;
}

bool Scanner::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool Scanner::isSpace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

vector<Token*> Scanner::Scan(ifstream &stream)
{
	char c = ' ';

	vector<Token*> tokens;

	stream >> c;

	while (!stream.eof())
	{
		while (isSpace(c))
		{
			if (!stream.eof())
				stream >> c;//; >> c;
			else
				break;
		}

		if (isAlpha(c))
		{
			stringstream ss;

			do
			{
				ss << c;

				if (!stream.eof())
					stream >> c;
				else
					break;
			}
			while (isalpha(c) || isDigit(c));

			string tempString;
			ss >> tempString;

			tokens.push_back(new TokenText(tempString));

			continue;
		}
		else if (c == '"')
		{
			stringstream ss;

			while (!stream.eof())
			{ 
				stream >> c;

				if (c == '"')
					break;

				ss << c;
			}

			string tempString;
			ss >> tempString;

			tokens.push_back(new TokenString(tempString));

			if (ss.eof())
				stream >> c;

			continue;
		}
		else if (c == '\'')
		{
			char c;

			if (!stream.eof())
				stream >> c;

			tokens.push_back(new TokenChar(c));

			if (!stream.eof())
				stream >> c;

			continue;
		}
		else if (isDigit(c))
		{
			stringstream ss;

			do
			{
				ss << c;

				if (!stream.eof())
					stream >> c;
				else
					break;
			}
			while (isDigit(c));

			int integer;
			ss >> integer;

			tokens.push_back(new TokenInteger(integer));

			continue;
		}
		else
		{
			stringstream ss;
			char oldC = c;

			do
			{
				ss << c;

				if (!stream.eof())
					stream >> c;
				else
					break;

				oldC = c;
			}
			while (!isalpha(c) && !isDigit(c) && !isSpace(c) &&
				c != ';' && c!= '(' && c != ')' && c != '{' && c != '}' && c != '~' && c!= '!' && c != '?' && // These are not used in complex operations
				(c == oldC || ( c!= '+' && c!= '-')));

			string tempString;
			ss >> tempString;

			tokens.push_back(new TokenOperator(tempString));

			continue;
		}
		/*
		else
		{
			cout << "Unexpected symbol: " << c << endl;
			if (!stream.eof())
				stream >> c;
		}*/

	}
	return tokens;
}

