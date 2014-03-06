#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Token;

class Token
{
public:
	virtual Token *Create(std::string str)=0;

	virtual std::string toString()=0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Test code ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

enum ETokenOperator
{
	NOT = 0,			BNOT,				EQUAL,				NOTEQUAL,		SHIFTLEFT,		SHIFTRIGHT,		OR,				AND,
	XOR,				PLUS,				MINUS,				MULTIPLY,		DIVIDE,			MODULO,			BOR,			BAND,
	ASSIGN,				SHIFTLEFTASSIGN,	SHIFTRIGHTASSIGN,	ORASSIGN,		ANDASSIGN,		XORASSIGN,		PLUSASSIGN,		MINUSASSIGN,
	MULTIPLYASSIGN,		DIVIDEASSIGN,		MODULOASSIGN,		BORASSIGN,		BANDASSIGN,		QUESTION,		COLON,			SEMICOLON,

	LEFTPARENTHESIS,	RIGHTPARENTHESIS,		LEFTCURLYBRACE,			RIGHTCURLYBRACE,
	LEFTSQUAREBRACKET,	RIGHTSQUAREBRACKET,		LEFTANGLEBRACKET,	RIGHTANGLEBRACKET,

	END
};

const std::string TokenOperatorNames[] =
{
	"~",				"!",				"==",				"!=",			"<<",			">>",			"|",			"&",
	"^",				"+",				"-",				"*",			"/",			"%",			"||",			"&&",
	"=",				"<<=",				">>=",				"|=",			"&=",			"^=",			"+=",			"-=",
	"*=",				"/=",				"%=",				"||=",			"&&=",			"?",			":",			";",

	"(",				")",					"{",					"}",
	"[",				"]",					"<",					">",
};

class TokenOperator : public Token
{
	ETokenOperator tokenOperator;
public:
	TokenOperator(std::string text)
	{
		for (int i = 0; i < ETokenOperator::END; i++)
		{
			if (TokenOperatorNames[i] == text)
			{
				tokenOperator = static_cast<ETokenOperator>(i);
				return;
			}
			
		}

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
		return nullptr;
	}

	virtual std::string toString()
	{
		return "operator: \t" + TokenOperatorNames[tokenOperator];
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
		return nullptr;
	}

	virtual std::string toString()
	{
		return "identifier: \t" + text;
	}

	const std::string getText()
	{
		return text;
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
		return nullptr;
	}

	virtual std::string toString()
	{
		return "string: \t\"" + text + "\"";
	}

	std::string getString()
	{
		return text;
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
		return nullptr;
	}

	virtual std::string toString()
	{
		return "char: \t\'" + static_cast<std::ostringstream*>( &(std::ostringstream() << c) )->str() + "\'";
	}

	char getChar()
	{
		return c;
	}


};

class TokenInteger : public Token
{
	int integer;
public:
	TokenInteger(int integer)
		: integer(integer)
	{
	}

	virtual Token *Create(std::string str)
	{
		return nullptr;
	}

	virtual std::string toString()
	{
		return "integer: \t" + static_cast<std::ostringstream*>( &(std::ostringstream() << integer) )->str();
	}

	int getInteger()
	{
		return integer;
	}
};
