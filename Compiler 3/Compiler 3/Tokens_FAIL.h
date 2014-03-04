#ifdef WANT_TO_USE_FILE
#include <string>

class Token;

#define SINGLE_ARG(...) __VA_ARGS__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// Metaprogrammerad kod under test ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ENUM_CLASS(_name,_enum,_enumstring) \
class _name : public Token\
{\
public:\
	static enum Enum\
	{
		_enum,\
		_ENUM_END\
	};\
	static std::string *enumstrings;\
	_name::Enum Value;\
	\
	_name(_name::Enum value)\
	{\
		Value = value;\
	}\
	\
	static void init()\
	{\
		_name::enumstrings = new std::string[_name::Enum::_ENUM_END];\
		std::string tempstring[] = { _enumstring };\
		_name::enumstrings = tempstring;\
	}\

	virtual Token *Create(std::string str)\
	{\
		for (unsigned char i = 0; i < _name::Enum::_ENUM_END; ++i)\
			{\
				if (enumstrings[i] == str)\
				{\
					return new _name(static_cast<_name::Enum>(i));\
				}\
			}\
			return nullptr;\
	}\
}
/*class _name : public Token\
{\
public:\
	static enum Enum\
	{\
		_enum\
	};\
	static char** enumstring = { _enumstring };\
	_name::Enum Value;\
	_name(_name::Enum value)\
	{\
		Value = value;\
	}\
	virtual Token *Create(char *str)\
	{\
		for (size_t i = 0; i < sizeof(*enumstring); ++i)\/*for(char* i = enumstring; i < sizeof(*enumstring); i++)\*-/
			{\
				if (*i == *str)\
				{\
					return new _name(i-*enumstring);\
				}\
			}\
			return nullptr;\
	}\
}*/

class Token
{
public:
	virtual Token *Create(std::string str)=0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Test code ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/*class _name : public Token
{
public:
	static enum Enum
	{
		a= 0,
		_ENUM_END
	};
	static std::string *enumstrings;
	_name::Enum Value;
	
	_name(_name::Enum value)
	{
		Value = value;
	}
	
	static void init()
	{
		_name::enumstrings = new std::string[_name::Enum::_ENUM_END];
		std::string tempstring[] = {"_enumstring"};
		_name::enumstrings = tempstring;
	}

	virtual Token *Create(std::string str)
	{
		for (unsigned char i = 0; i < _name::Enum::_ENUM_END; ++i)
			{
				if (enumstrings[i] == str)
				{
					return new _name(static_cast<_name::Enum>(i));
				}
			}
			return nullptr;
	}
};*/


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Under test->

//ENUM_CLASS(TESTMOJDFS, AETT, "AETT");

ENUM_CLASS(tOperator,
		   SINGLE_ARG(
		   NOT = 0,			BNOT,				EQUAL,			NOTEQUAL,		SHIFTLEFT,	SHIFTRIGHT,	OR,			AND,
		   XOR,				PLUS,				MINUS,			MULTIPLY,		DIVIDE,		MODULO,		BOR,		BAND,
		   SHIFTLEFTEQUAL,	SHIFTRIGHTEQUAL,	OREQUAL,		ANDEQUAL,		XOREQUAL,	PLUSEQUAL,	MINUSEQUAL,	MULTIPLYEQUAL,
		   DIVIDEEQUAL,		MODULOEQUAL,		BOREQUAL,		BANDEQUAL,		QUESTION,	COLON),
		   SINGLE_ARG(
		   "~",				"!",				"==",			"!=",			"<<",		">>",		"|",		"&",
		   "^",				"+",				"-",			"*",			"/",		"%",		"||",		"&&",
		   "<<=",			">>=",				"|=",			"&=",			"^=",		"+=",		"-=",		"*=",
		   "/=",			"%=",				"||=",			"&&=",			"?",		":"));

/*enum operatorEnum
{

};*/
#endif