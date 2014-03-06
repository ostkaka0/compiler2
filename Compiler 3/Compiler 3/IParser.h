#pragma once

#include <vector>

class Token;
class Expression;
class Statement;

class IParser
{
public:
	virtual std::vector<Statement*> ParseStmt(std::vector<Token*> tokens, bool multiStmts)=0;
	virtual Expression *ParseExpr(std::vector<Token*> tokens, int index)=0;
};