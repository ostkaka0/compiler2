#pragma once

#include <vector>

class Token;
class Expression;
class Statement;

class Parser
{
	long myIndex;
	Expression *stackExpr;

public:
	Parser();
	Expression *ParseExpr(std::vector<Token*> tokens, int index);
	std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts);
};