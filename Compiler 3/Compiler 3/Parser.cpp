#include "Parser.h"
#define NextToken(error) next(tokens, index, error)
#define NextToken() next (tokens, index)

using namespace std;

inline Token *next(std::vector<Token*> tokens, unsigned int index ,const std::string error) {
	if (index < tokens.size()) {
		return tokens[index];
	}
	else {
		cerr << error << endl;
		return new TokenNull();
	}
}

inline Token *next(std::vector<Token*> tokens, unsigned int index) {
	if (index < tokens.size()) {
		return tokens[index];
	}
	else {
		return new TokenNull();
	}
}

#pragma region Parse_Statement

	//vector<Statement*> parsePreprocessor(TokenPreprocessor *token);
	vector<Statement*> Parser::parseOperatorStmt(	vector<Token*> tokens)
	{
		return std::vector<Statement*>();
	}

	vector<Statement*> Parser::parseTextStmt(		vector<Token*> tokens)
	{
		return std::vector<Statement*>();
	}

	vector<Statement*> Parser::parseStringStmt(	vector<Token*> tokens)
	{
		return std::vector<Statement*>();
	}

	vector<Statement*> Parser::parseCharStmt(		vector<Token*> tokens)
	{
		return std::vector<Statement*>();
	}

	vector<Statement*> Parser::parseIntegerStmt(	vector<Token*> tokens)
	{
		return std::vector<Statement*>();
	}

	//vector<Statement*> Parser::parseFloat(TokenFloat *token);
	//vector<Statement*> Parser::parseDouble(TokenDouble *token);
#pragma endregion
#pragma region Parse_Expression

	//vector<Expression*> parsePreprocessor(TokenPreprocessor *token);
	Expression* parseOperatorExpr(	vector<Token*> tokens)
	{
		return nullptr;
	}

	Expression* parseTextExpr(		vector<Token*> tokens)
	{
		return nullptr;
	}

	Expression* parseStringExpr(	vector<Token*> tokens)
	{
		return nullptr;
	}

	Expression* parseCharExpr(		vector<Token*> tokens)
	{
		return nullptr;
	}

	Expression* parseIntegerExpr(	vector<Token*> tokens)
	{
		return nullptr;
	}

	//vector<Expression*> parseFloat(TokenFloat *token);
	//vector<Expression*> parseDouble(TokenDouble *token);
#pragma endregion

vector<Statement*> Parser::ParseStmt(vector<Token*> tokens, bool multiStmts)
{
	/*int index = 0;
	std::vector<Statement*> statements;

	while (index < tokens.size())
	{
		size_t tokenType = typeid((NextToken())).hash_code();

		map<size_t, std::vector<Statement*>(*)(std::vector<Token*>)> handlers;
		//
		//handlers.insert(pair<size_t, std::vector<Statement*>(*)(std::vector<Token*>)>
		//	(typeid(TokenOperator).hash_code(), parseOperatorExpr));
	}
	*/
	return vector<Statement*>();
}

Expression *Parser::ParseExpr(vector<Token*> tokens, int index)
{
	return nullptr;
}