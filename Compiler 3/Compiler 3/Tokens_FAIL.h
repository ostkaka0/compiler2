#ifdef WANodeT_TO_USE_FILE
#include <string>

class Token;

#define SINodeGLE_ARG(...) __VA_ARGS__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// Metaprogrammerad kod under test ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ENodeUM_CLASS(_name,_enum,_enumstring) \
class _name : public Token\
{\
public:\
	static enum Enum\
	{
		_enum,\
		_ENodeUM_ENodeD\
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
		_name::enumstrings = new std::string[_name::Enum::_ENodeUM_ENodeD];\
		std::string tempstring[] = { _enumstring };\
		_name::enumstrings = tempstring;\
	}\

	virtual Token *Create(std::string str)\
	{\
		for (unsigned char i = 0; i < _name::Enum::_ENodeUM_ENodeD; ++i)\
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
		_ENodeUM_ENodeD
	};
	static std::string *enumstrings;
	_name::Enum Value;
	
	_name(_name::Enum value)
	{
		Value = value;
	}
	
	static void init()
	{
		_name::enumstrings = new std::string[_name::Enum::_ENodeUM_ENodeD];
		std::string tempstring[] = {"_enumstring"};
		_name::enumstrings = tempstring;
	}

	virtual Token *Create(std::string str)
	{
		for (unsigned char i = 0; i < _name::Enum::_ENodeUM_ENodeD; ++i)
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

//ENodeUM_CLASS(TESTMOJDFS, AETT, "AETT");

ENodeUM_CLASS(tOperator,
		   SINodeGLE_ARG(
		   NodeOT = 0,			BNodeOT,				EQUAL,			NodeOTEQUAL,		SHIFTLEFT,	SHIFTRIGHT,	OR,			ANodeD,
		   XOR,				PLUS,				MINodeUS,			MULTIPLY,		DIVIDE,		MODULO,		BOR,		BANodeD,
		   SHIFTLEFTEQUAL,	SHIFTRIGHTEQUAL,	OREQUAL,		ANodeDEQUAL,		XOREQUAL,	PLUSEQUAL,	MINodeUSEQUAL,	MULTIPLYEQUAL,
		   DIVIDEEQUAL,		MODULOEQUAL,		BOREQUAL,		BANodeDEQUAL,		QUESTIONode,	COLONode),
		   SINodeGLE_ARG(
		   "~",				"!",				"==",			"!=",			"<<",		">>",		"|",		"&",
		   "^",				"+",				"-",			"*",			"/",		"%",		"||",		"&&",
		   "<<=",			">>=",				"|=",			"&=",			"^=",		"+=",		"-=",		"*=",
		   "/=",			"%=",				"||=",			"&&=",			"?",		":"));

/*enum operatorEnum
{

};*/
#endif