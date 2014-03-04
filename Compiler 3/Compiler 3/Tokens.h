#include <string>
#include <vector>
#include <iostream>

class Token;

class Token
{
public:
	virtual Token *Create(std::string str)=0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Test code ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

enum ETokenOperator
{
	NOT = 0,			BNOT,				EQUAL,			NOTEQUAL,		SHIFTLEFT,	SHIFTRIGHT,	OR,			AND,
	XOR,				PLUS,				MINUS,			MULTIPLY,		DIVIDE,		MODULO,		BOR,		BAND,
	SHIFTLEFTEQUAL,		SHIFTRIGHTEQUAL,	OREQUAL,		ANDEQUAL,		XOREQUAL,	PLUSEQUAL,	MINUSEQUAL,	MULTIPLYEQUAL,
	DIVIDEEQUAL,		MODULOEQUAL,		BOREQUAL,		BANDEQUAL,		QUESTION,	COLON,		SEMICOLON,

	LEFTPARENTHESIS,	RIGHTPARENTHESIS,	LEFTCURLYBRACE,		RIGHTCURLYBRACE,
	LEFTSQUAREBRACKET,	RIGHTSQUAREBRACKET,	LEFTANGLEBRACKET,	RIGHTANGLEBRACKET
};

std::string TokenOperatorNames[] =
{
	"~",				"!",				"==",			"!=",			"<<",		">>",		"|",		"&",
	"^",				"+",				"-",			"*",			"/",		"%",		"||",		"&&",
	"<<=",				">>=",				"|=",			"&=",			"^=",		"+=",		"-=",		"*=",
	"/=",				"%=",				"||=",			"&&=",			"?",		":",		";",

	"(",				")",				"{",				"}",
	"[",				"]",				"<",				">",
};

class TokenOperator : public Token
{
	ETokenOperator tokenOperator;
public:
	TokenOperator(std::string text)
	{
		for (int i = 0; i < sizeof(TokenOperatorNames); i++)
		{
			if (TokenOperatorNames[i] == text)
			{
				tokenOperator = (ETokenOperator)i;
			}
			return;
		}

		std::cout << "Invalid operator: " << text << ".\n";
		std::cerr << "Invalid operator: " << text << ".\n";
		std::cin.get();
		exit(-1);
	}

	ETokenOperator getOperator()
	{
		return tokenOperator;
	}

	virtual Token *Create(std::string str)
	{
		
	}
};

class TokenText : public Token
{
	std::string text;
public:
	TokenText(std::string text)
		: text(text)
	{
	}

	virtual Token *Create(std::string str)
	{
	}
};

class TokenString : public Token
{
	std::string text;
public:
	TokenString(std::string text)
		: text(text)
	{
	}

	virtual Token *Create(std::string str)
	{
	}
};

class TokenChar : public Token
{
	char c;
public:
	TokenChar(char c)
		: c(c)
	{
	}

	virtual Token *Create(std::string str)
	{
	}

	char getChar()
	{
		return c;
	}
};

