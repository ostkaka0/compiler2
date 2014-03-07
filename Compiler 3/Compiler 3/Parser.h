#include <map>

#include "AParser.h"

#include "Tokens.h"
#include "Node.h"



class Parser : AParser {
protected:

#pragma region Parse_Statement

	//virtual std::vector<Statement*> parsePreprocessor(TokenPreprocessor *token);
	virtual std::vector<Statement*> parseOperatorStmt(	std::vector<Token*> tokens);
	virtual std::vector<Statement*> parseTextStmt(		std::vector<Token*> tokens);
	virtual std::vector<Statement*> parseStringStmt(	std::vector<Token*> tokens);
	virtual std::vector<Statement*> parseCharStmt(		std::vector<Token*> tokens);
	virtual std::vector<Statement*> parseIntegerStmt(	std::vector<Token*> tokens);
	//virtual std::vector<Statement*> parseFloat(TokenFloat *token);
	//virtual std::vector<Statement*> parseDouble(TokenDouble *token);
#pragma endregion
#pragma region Parse_Expression

	//virtual std::vector<Expression*> parsePreprocessor(TokenPreprocessor *token);
	virtual Expression* parseOperatorExpr(	std::vector<Token*> tokens);
	virtual Expression* parseTextExpr(		std::vector<Token*> tokens);
	virtual Expression* parseStringExpr(	std::vector<Token*> tokens);
	virtual Expression* parseCharExpr(		std::vector<Token*> tokens);
	virtual Expression* parseIntegerExpr(	std::vector<Token*> tokens);
	//virtual std::vector<Expression*> parseFloat(TokenFloat *token);
	//virtual std::vector<Expression*> parseDouble(TokenDouble *token);
#pragma endregion

public:
	virtual std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts);

	virtual Expression *ParseExpr(std::vector<Token*> tokens, int index);

};