#include "IParser.h"

class TokenPreprocessor;//

class TokenOperator;
class TokenText;
class TokenString;
class TokenChar;
class TokenInteger;
class TokenFloat;//
class tokenDouble;//

class AParser : public IParser
{
protected:
#pragma region Parse_Statement

	//virtual std::vector<Statement*> parsePreprocessor(TokenPreprocessor *token)=0;
	virtual std::vector<Statement*> parseOperatorStmt(	std::vector<Token*> tokens)=0;
	virtual std::vector<Statement*> parseTextStmt(		std::vector<Token*> tokens)=0;
	virtual std::vector<Statement*> parseStringStmt(	std::vector<Token*> tokens)=0;
	virtual std::vector<Statement*> parseCharStmt(		std::vector<Token*> tokens)=0;
	virtual std::vector<Statement*> parseIntegerStmt(	std::vector<Token*> tokens)=0;
	//virtual std::vector<Statement*> parseFloat(TokenFloat *token)=0;
	//virtual std::vector<Statement*> parseDouble(TokenDouble *token)=0;
#pragma endregion
#pragma region Parse_Expression

	//virtual std::vector<Expression*> parsePreprocessor(TokenPreprocessor *token)=0;
	virtual Expression* parseOperatorExpr(	std::vector<Token*> tokens)=0;
	virtual Expression* parseTextExpr(		std::vector<Token*> tokens)=0;
	virtual Expression* parseStringExpr(	std::vector<Token*> tokens)=0;
	virtual Expression* parseCharExpr(		std::vector<Token*> tokens)=0;
	virtual Expression* parseIntegerExpr(	std::vector<Token*> tokens)=0;
	//virtual std::vector<Expression*> parseFloat(TokenFloat *token)=0;
	//virtual std::vector<Expression*> parseDouble(TokenDouble *token)=0;
#pragma endregion
public:
	virtual std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts)=0;
	virtual Expression *ParseExpr(std::vector<Token*> tokens, int index)=0;
};