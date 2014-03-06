#include <map>

#include "AParser.h"

#include "Tokens.h"
#include "Node.h"

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

class Parser : AParser {
protected:
#pragma region Parse_Statement

	//virtual std::vector<Statement*> parsePreprocessor(TokenPreprocessor *token);
	virtual std::vector<Statement*> parseOperatorStmt(TokenOperator *token) {

	}

	virtual std::vector<Statement*> parseTextStmt(TokenText *token) {

	}

	virtual std::vector<Statement*> parseStringStmt(TokenString *token) {

	}

	virtual std::vector<Statement*> parseCharStmt(TokenChar *token) {

	}

	virtual std::vector<Statement*> parseIntegerStmt(TokenInteger *token) {

	}

	//virtual std::vector<Statement*> parseFloat(TokenFloat *token);
	//virtual std::vector<Statement*> parseDouble(TokenDouble *token);
#pragma endregion
#pragma region Parse_Expression

	//virtual std::vector<Expression*> parsePreprocessor(TokenPreprocessor *token);
	virtual std::vector<Expression*> parseOperatorExpr(TokenOperator *token) {

	}

	virtual std::vector<Expression*> parseTextExpr(TokenText *token) {

	}

	virtual std::vector<Expression*> parseStringExpr(TokenString *token) {

	}

	virtual std::vector<Expression*> parseCharExpr(TokenChar *token) {

	}

	virtual std::vector<Expression*> parseIntegerExpr(TokenInteger *token) {

	}

	//virtual std::vector<Expression*> parseFloat(TokenFloat *token);
	//virtual std::vector<Expression*> parseDouble(TokenDouble *token);
#pragma endregion
public:
	virtual std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts) {
		int index = 0;
		std::vector<Statement*> statements;

		while (index < tokens.size()) {
			size_t tokenType = typeid((NextToken())).hash_code();

			map<size_t, std::vector<Statement*>(*)(std::vector<Token*>)> handlers;
			//
			handlers.insert(pair<size_t, std::vector<Statement*>(*)(std::vector<Token*>)>
				(typeid(TokenOperator).hash_code(), parseOperatorExpr));



		}
	}

	virtual Expression *ParseExpr(std::vector<Token*> tokens, int index) {

	}

};