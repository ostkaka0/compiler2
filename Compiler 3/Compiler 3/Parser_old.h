#pragma once

#include <vector>

class Token;
class Expression;
class Statement;

class Parser_old
{
	long myIndex;
	Expression *stackExpr;

public:
	Parser_old();
	Expression *ParseExpr(std::vector<Token*> tokens, int index);
	std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts);
};